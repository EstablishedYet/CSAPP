#include<unistd.h>
#include<csignal>
#include<cstdio>
#include<cstdlib>
#include<cerrno>
#include<cstring>

sighandler_t Signal(int sig,sighandler_t handler)
{
    struct sigaction action,old_action;
    action.sa_handler=handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags=SA_RESTART;
    if(sigaction(sig,&action,&old_action)<0)
    {
        fprintf(stderr,"%s: %s\n","sigaction error",strerror(errno));
        exit(1);
    }
    return old_action.sa_handler;
}
// signal