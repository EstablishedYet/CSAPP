#include<cstdio>
#include<sys/types.h>
#include<unistd.h>
int main()
{
    pid_t cur_pid,par_pid;
    cur_pid=getpid();
    par_pid=getppid();
    printf("%d,%d",cur_pid,par_pid);
    return 0;
}