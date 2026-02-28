// #include<cstdlib>
// #include<cstdio>
// #include<cerrno>
// #include<csignal>
// #include<unistd.h>
#include"/home/established/CSAPP/Chapter8/19/sio.h"

const int MAXBUF=128;

void unix_error(char s[])
{
    fprintf(stderr,"%s: %s\n",s,strerror(errno));
    exit(1);
}
struct sigaction a;
void handler1(int sig)
{
    // char ch[];
    int old_error=errno;
    pid_t pid;
    if((pid=waitpid(-1,NULL,0))<0)
    {
        char ch[]="Wait error";
        sio_error(ch);

    }
    char ch[]="Handler reap child ";
    sio_puts(ch);
    sio_putl(long(pid));
    char ch1[]="\n";
    sio_puts(ch1);
    sleep(1);
    errno=old_error;
    return;
}

void handler2(int sig)
{
    int old_error=errno;
    pid_t pid;
    while((pid=waitpid(-1,NULL,0))>0)
    {
        char ch[]="Handler reap child ";
        sio_puts(ch);
        sio_putl(long(pid));
        char ch1[]="\n";
        sio_puts(ch1);
    }
    if(errno!=ECHILD)
    {
        char ch[]="Wait error";
        sio_error(ch);
    }
    sleep(1);
    errno=old_error;
    return;
}

int main()
{
    char buf[MAXBUF];

    if(signal(SIGCHLD,handler2)==SIG_ERR)
    {
        char ch[]="Signal error";
        unix_error(ch);

    }
    for(int i=0;i<3;++i)
    {
        if(fork()==0)
        {
            printf("Hello from child %d\n",getpid());
            exit(0);
        }
    }
    if(read(STDIN_FILENO,buf,sizeof(buf))==0)
    {
        char ch[]="read error";
        unix_error(ch);

    }
    printf("Parent processing\n");
    while(true)
    {

    }
    return 0;
}

