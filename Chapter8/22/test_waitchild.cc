#include<cstdlib>
#include<cstdio>
#include<unistd.h>
#include<cstring>
#include<cerrno>
#include<csignal>
#include<wait.h>

volatile sig_atomic_t pid;

void SIGCHLD_handler(int sig)
{
    int old_erron=errno;
    pid=waitpid(-1,NULL,0);
    errno=old_erron;
    return;
}

int main()
{
    sigset_t mask,prev_mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGCHLD);

    signal(SIGCHLD,SIGCHLD_handler);
    while(true)
    {
        sigprocmask(SIG_BLOCK,&mask,&prev_mask);
        if(fork()==0)
            exit(0);
        pid=0;
        sigprocmask(SIG_SETMASK,&prev_mask,NULL);
        while(!pid)
        {
            // pause();
        }
        printf(".");
    }
    return 0;
}