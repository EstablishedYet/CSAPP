#include"my_socket_helpers.h"
#include"/home/established/CSAPP/Chapter10/2/robust_io.h"

int main(int argc,char **argv)
{
    if(argc!=3)
    {
        fprintf(stderr,"usage: ./echo_client.out <address> <port>\n");
        exit(1);
    }
    int clientfd;
    if((clientfd=open_clientfd(argv[1],argv[2]))==-1)
    {
        // printf("")
        exit(1);
    }
    rio_t rio;
    rio_readinitb(&rio,clientfd);
    char buf[MAXLINE];
    // int circle=0;
    while(fgets(buf,MAXLINE,stdin)!=NULL)
    {
        // printf("cir: %d\n",circle++);
        if(rio_writen(clientfd,buf,strlen(buf))<0)
        {
            fprintf(stderr,"rio_weiten error\n");
            exit(1);
        }
        if(rio_readlineb(&rio,buf,MAXLINE)<0)
        {
            fprintf(stderr,"rio_readlineb error\n");
            exit(1);
        }
        fputs(buf,stdout);
    }
    close(clientfd);
    exit(0);
}