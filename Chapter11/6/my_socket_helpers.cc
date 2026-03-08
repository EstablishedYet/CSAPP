#include"my_socket_helpers.h"

int open_clientfd(char *hostname,char *port)
{
    addrinfo *p,*listp,hint;
    memset(&hint,0,sizeof(addrinfo));
    hint.ai_socktype=SOCK_STREAM;
    hint.ai_flags=AI_ADDRCONFIG;
    int rc,socketfd;
    if((rc=getaddrinfo(hostname,port,&hint,&listp))!=0)
    {
        fprintf(stderr,"getaddrinfo error: %s\n",gai_strerror(rc));
        exit(0);
    }
    for(p=listp;p;p=p->ai_next)
    {
        if((socketfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0)
        {
            continue;
        }
        if((connect(socketfd,p->ai_addr,p->ai_addrlen))==0)
        {
            break;
        }
        close(socketfd);
    }
    freeaddrinfo(listp);
    if(!p)
    {
        fprintf(stderr,"connect fail\n");
        return -1;
    }
    else
    {
        return socketfd;
    }
}

int open_listenfd(char *port)
{
    addrinfo *p,*listp,hint;
    memset(&hint,0,sizeof(addrinfo));
    hint.ai_socktype=SOCK_STREAM;
    hint.ai_flags=AI_PASSIVE|AI_ADDRCONFIG;
    int rc,socketfd;
    int optval=1;
    if((rc=getaddrinfo(NULL,port,&hint,&listp))!=0)
    {
        fprintf(stderr,"getaddrinfo error: %s\n",gai_strerror(rc));
        exit(1);
    }    
    for(p=listp;p;p=p->ai_next)
    {
        if((socketfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0)
        {
            continue;
        }
        setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));
        if((bind(socketfd,p->ai_addr,p->ai_addrlen))==0)
        {
            break;
        }
        close(socketfd);
    }
    freeaddrinfo(listp);
    if(!p)
    {
        return -1;
    }
    if(listen(socketfd,LISTEN_QUE_LEN)!=0)
    {
        close(socketfd);
        return -1;
    }
    return socketfd;
}
