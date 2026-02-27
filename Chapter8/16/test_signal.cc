#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<cerrno>
#include<csignal>

void my_SIGINT_handler(int sig)
{
    printf("Caught SIGINT.\n");
    exit(0);
}

int main()
{
    sighandler_t  sig_return;
    sig_return=signal(SIGINT,my_SIGINT_handler);
    if(sig_return==SIG_ERR)
    {
        fprintf(stderr,"Signal Error: %s\n",strerror(errno));
        exit(0);
    }
    pause();
    return 0;
}