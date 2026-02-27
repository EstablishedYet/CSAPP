#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<cerrno>
#include<csignal>

int main()
{
    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        pause();
    }
    kill(pid,SIGKILL);
    return 0;
}