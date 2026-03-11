#include"/home/established/CSAPP/Chapter11/6/my_socket_helpers.h"
#include"/home/established/CSAPP/Chapter10/2/robust_io.h"
#include<strings.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<wait.h>
#include<csignal>
#include"/home/established/CSAPP/Chapter8/19_sio/sio.h"
#include<sys/select.h>

void doit(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri,char *filename,char *cgiargs);
void serve_static(int fd,char *filename);
void get_filetype(char *filename,char *filetype);
void serve_dynamic(int fd,char *filename,char *cgiargs);
void clienterror(int fd,const char *cause,const char *errnum,const char *shortmsg,const char *longmsg);
void command();

void handler1(int sig)
{
    sio_puts("Caught SIGPIPE\n");
    return;
}

void handler2(int sig)
{
    int prev_error=errno;
    while(waitpid(-1,NULL,WNOHANG)>0)
    {
    }
    errno=prev_error;
}


int main(int argc,char **argv)
{
    fd_set read_set,ready_set;
    signal(SIGPIPE,handler1);
    signal(SIGCHLD,handler2);
    if(argc!=2)
    {
        fprintf(stderr,"usage: %s <port>",argv[0]);
        exit(1);
    }
    sockaddr_storage sock;
    socklen_t sock_len=sizeof(sock);
    int listenfd,connectfd;
    char ch_host[MAXLINE],ch_serv[MAXLINE];
    listenfd=open_listenfd(argv[1]);
    if(listenfd<0)
    {
        unix_error("open_listenfd error");
    }
    FD_SET(STDIN_FILENO,&read_set);
    FD_SET(listenfd,&read_set);
    while(true)
    {
        ready_set=read_set;
        select(listenfd+1,&ready_set,NULL,NULL,NULL);
        if(FD_ISSET(listenfd,&ready_set))
        {
            connectfd=accept(listenfd,(sockaddr *)&sock,&sock_len);
            if(connectfd<0)
            {
                unix_error("accept error");;
            }
            if(getnameinfo((sockaddr *)&sock,sock_len,ch_host,MAXLINE,ch_serv,MAXLINE,0))
            {
                unix_error("getnameinfo error");
            }
            printf("Connected with %s:%s\n",ch_host,ch_serv);
            if(fork()==0)
            {
                close(listenfd);
                doit(connectfd);
                close(connectfd);
                exit(0);
            }
            close(connectfd);
        }
        if(FD_ISSET(STDIN_FILENO,&ready_set))
        {
            command();
        }
    }
    exit(0);
}

void doit(int fd)
{
    rio_t rio;
    rio_readinitb(&rio,fd);
    char header[MAXLINE];
    int rc_rlb;
    rc_rlb=Rio_readlineb(&rio,header,MAXLINE);
    char uri[MAXLINE],filename[MAXLINE],cgiargs[MAXLINE],func[MAXLINE];
    sscanf(header,"%s %s",func,uri);
    if(strcmp(func,"GET"))
    {
        clienterror(fd,func,"501","Not implemented","Tiny does not implement this method: ");
        return;
    }
    read_requesthdrs(&rio);
    int if_static;
    if_static=parse_uri(uri,filename,cgiargs);
    if(if_static)
    {
        serve_static(fd,filename);
    }
    else
    {
        serve_dynamic(fd,filename,cgiargs);
    }
    return;
}

void read_requesthdrs(rio_t *rp)
{
    char buf[8192];
    rio_readlineb(rp,buf,MAXLINE);
    while(strcasecmp(buf,"\r\n"))
    {
        printf("%s",buf);
        rio_readlineb(rp,buf,MAXLINE);
    }
    return;
}

void clienterror(int fd,const char *cause,const char *errnum,const char *shortmsg,const char *longmsg)
{
    char buf[512],body[8192];

    sprintf(body,"<html><title>Tiny Error</title>\r\n");
    sprintf(body,"%s<body bgcolor=\"ffffff\">\r\n",body);
    sprintf(body,"%s<p>%s: %s</p>\r\n",body,errnum,shortmsg);
    sprintf(body,"%s<p>%s: %s</p>\r\n",body,longmsg,cause);
    sprintf(body,"%s<hr>\r\n",body);
    sprintf(body,"%s<em>The Tiny Web server</em></body></html>\r\n",body);

    sprintf(buf,"HTTP/1.0 %s %s\r\n",errnum,shortmsg);
    sprintf(buf,"%sConnection: close\r\n",buf);
    sprintf(buf,"%sContent-Length: %d\r\n",buf,strlen(body));
    sprintf(buf,"%sContent-Type: text/html\r\n\r\n",buf);
    Rio_writen(fd,buf,strlen(buf));
    Rio_writen(fd,body,strlen(body));
    return;
}

int parse_uri(char *uri,char *filename,char *cgiargs)
{
    char *p1,*p2;
    // cgiargs=NULL;
    strcpy(cgiargs,"");
    int if_static=1;
    if(p1=strstr(uri,"cgi-bin"))
    {
        if_static=0;
        if(p2=strchr(p1,'?'))
        {
            *p2='\0';
            strcpy(cgiargs,p2+1);
        }
    }
    strcpy(filename,".");
    strcat(filename,uri);
    if(!strcmp(filename,"./"))
    {
        strcpy(filename,"./index.html");
    }
    return if_static;
}

void serve_static(int fd,char *filename)
{
    struct stat filestat;
    if(stat(filename,&filestat)!=0)
    {
        clienterror(fd,filename,"404","Not Found","There is no such file in the Tiny");
        return;
    }
    if(!S_ISREG(filestat.st_mode)||!(S_IRUSR&filestat.st_mode))
    {
        clienterror(fd,filename,"403","Forbidden","Tiny couldn't read the file");
        return;
    }
    int filesize=filestat.st_size;
    char header[512];
    char filetype[64];
    get_filetype(filename,filetype);
    sprintf(header,"HTTP/1.0 200 OK\r\n");
    sprintf(header,"%sConnection: close\r\n",header);
    sprintf(header,"%sContent-Length: %d\r\n",header,filesize);
    sprintf(header,"%sContent-Type: %s\r\n\r\n",header,filetype);
    Rio_writen(fd,header,strlen(header));
    int filefd=open(filename,O_RDONLY,0);
    char buf[filesize];
    // rio_t filerio;
    // rio_readinitb(&filerio,filefd);
    Rio_readn(filefd,buf,filesize);
    int rc;
    rc=Rio_writen(fd,buf,filesize);
    close(filefd);
    // while((Rio_readlineb(&filerio,buf,MAXLINE)))
    // {
    //     Rio_writen(fd,buf,strlen(buf));
    // }
    return;
}

void get_filetype(char *filename,char *filetype)
{
    char *p;
    if(p=strchr(filename,'.'))
    {
        if(strcasecmp(p,".html"))
            strcpy(filetype,"text/html");
        else if(strcasecmp(p,".jpg")||strcasecmp(p,".jpeg"))
            strcpy(filetype,"image/jpeg");
    }
    else
    {
        strcpy(filetype,"text/plain");
    }
}

void serve_dynamic(int fd,char *filename,char *cgiargs)
{
    struct stat filestat;
    // stat(filename,&filestat);
    if(stat(filename,&filestat)!=0)
    {
        clienterror(fd,filename,"404","Not Found","There is no such file in the Tiny");
        return;
    }
    if(!S_ISREG(filestat.st_mode)||!(S_IXUSR&filestat.st_mode))
    {
        clienterror(fd,filename,"403","Forbidden","Tiny couldn't execute the file");
        return;
    }
    char header[MAXLINE];
    char *emptylist[]={NULL};
    if(fork()==0)
    {
        dup2(fd,1);
        sprintf(header,"HTTP/1.0 200 OK\r\n");
        Rio_writen(fd,header,strlen(header));
        setenv("QUERY_STRING",cgiargs,1);
        execve(filename,emptylist,environ);
        close(fd);
    }
    wait(NULL);
    return;
}