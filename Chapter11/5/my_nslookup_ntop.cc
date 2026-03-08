#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<cstdio>
#include<netdb.h>
#include<cstdlib>
#include<cstring>
#include<typeinfo>
// sockadd

const int MAXLEN=16;

int main(int argc,char **argv)
{
    addrinfo *p,*listp,hints;
    char ch_host[MAXLEN],ch_sevice[MAXLEN];
    if(argc!=2)
    {
        fprintf(stderr,"Usage:./my_nslookup.out <domain_name>\n");
        exit(1);
    }
    memset(&hints,0,sizeof(addrinfo));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    hints.ai_protocol=0;
    // hints.ai_flags=
    int rc;
    if((rc=getaddrinfo(argv[1],NULL,&hints,&listp))!=0)
    {
        fprintf(stderr,"getaddrinfo error: %s\n",gai_strerror(rc));
        exit(1);
    }
    for(p=listp;p;p=p->ai_next)
    {
        // if((rc=getnameinfo(p->ai_addr,p->ai_addrlen,ch_host,MAXLEN,NULL,0,NI_NUMERICHOST))!=0)
        // {
        //     fprintf(stderr,"getnameinfo error: %s\n",gai_strerror(rc));
        //     exit(1);
        // }
        inet_ntop(AF_INET,(char *)(p->ai_addr->sa_data)+2,ch_host,MAXLEN);
        printf("Address: %s\n",ch_host);
        printf("%s\n",typeid((char *)&(p->ai_addr->sa_data)).name());
    }
    freeaddrinfo(listp);
    return 0;
}