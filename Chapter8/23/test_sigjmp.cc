#include<csetjmp>
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<csignal>
#include"/home/established/CSAPP/Chapter8/19_sio/sio.h"

sigjmp_buf buf;

void handler1(int sig)
{
    siglongjmp(buf,1);
}


int main()
{
    if(!sigsetjmp(buf,1))
    {
        signal(SIGINT,handler1);
        // printf("Starting\n");
        char ch[]="Starting\n";
        sio_puts(ch);
    }
    else
    {
        char ch[]="Restarting\n";
        sio_puts(ch);
        // execve()
        // printf();
    }

    while(true)
    {
        // printf("Processing\n");
        sio_puts("Processing\n");
        sleep(1);
    }
    return 0;
}
