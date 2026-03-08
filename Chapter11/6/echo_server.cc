#include"my_socket_helpers.h"
#include"/home/established/CSAPP/Chapter10/2/robust_io.h"

void echo(int serverfd)
{
    printf("Echo started\n");
    rio_t rio;
    rio_readinitb(&rio,serverfd);
    char buf[MAXLINE];
    ssize_t n;
    while((n=Rio_readlineb(&rio,buf,MAXLINE))!=0)
    {
        printf("Received %d bytes\n",(int)n);
        Rio_writen(serverfd,buf,n);
    }
    return;
    // while()
}

int main(int argc,char **argv)
{
    if(argc!=2)
    {
        unix_error("Usage: ./echo_server.out <port>");
    }
    int serverfd,listenfd;
    if((serverfd=open_listenfd(argv[1]))<0)
    {
        unix_error("open_listenfd error");
    }
    sockaddr_storage addr;
    socklen_t len=sizeof(sockaddr_storage);
    char ch_host[MAXLINE],ch_port[MAXLINE];
    while((listenfd=accept(serverfd,(sockaddr *)&addr,&len))>-1)
    {
        getnameinfo((sockaddr *)&addr,len,ch_host,MAXLINE,ch_port,MAXLINE,0);
        printf("Connected to %s: %s\n",ch_host,ch_port);
        echo(listenfd);
        close(listenfd);
    }
    unix_error("accept error");
}