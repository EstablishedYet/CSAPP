#include<csignal>
#include<cstdlib>
#include<cstdio>
#include<cerrno>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    sigset_t sigmask,prev_sigmask;
    printf("%d\n",getpid());
    sigemptyset(&sigmask);
    sigaddset(&sigmask,SIGINT);
    sigprocmask(SIG_BLOCK,&sigmask,&prev_sigmask);
    // printf("%d\n",prev_sigmask);
    sleep(100);
    return 0;
}