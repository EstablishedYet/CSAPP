#include<unistd.h>
#include<cstdio>
#include<cstring>
#include<cerrno>
#include<stdlib.h>
#include<sys/types.h>
// #include<

pid_t Fork();

int main()
{
    pid_t pid;
    int x=1;
    pid=Fork();
    if(pid==0)
    {
        fprintf(stdout,"child: %d\n",++x);
        printf("Child's Parent pid: %d\nChild's pid:%d\n",getppid(),getpid());
        exit(0);
    }
    printf("Parent: %d\n",--x);
    printf("Parent's pid: %d\n",getpid());
    exit(0);
}

pid_t Fork()
{
    pid_t pid;
    pid=fork();
    if(pid<0)
    {
        fprintf(stderr,"fork error: %s\n",strerror(errno));
        exit(0);
    }
    return pid;

}