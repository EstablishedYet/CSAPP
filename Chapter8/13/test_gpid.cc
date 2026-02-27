#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<cerrno>

int main()
{
    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        printf("Child, grp %d\n",getpgrp());
        printf("Child, pid %d\n",getpid());
    }
    else
    {
        printf("Parent, grp %d\n",getpgrp());
        printf("Parent, pid %d\n",getpid());
    }
    return 0;
}