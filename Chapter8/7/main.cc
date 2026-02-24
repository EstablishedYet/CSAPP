#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<cstdio>
#include<cstring>
#include<cerrno>
#include<cstdlib>
pid_t Fork();

int main()
{
    pid_t pid;
    int status;
    pid=Fork();
    if(pid==0)
    {
        printf("The child\n");
        exit(2);
    }
    else
    {
        pid=waitpid(-1,&status,0);
        if(WIFEXITED(status))
        {
            printf("Child exit with %d\n",WEXITSTATUS(status));
        }
    }
    exit(0);
    // WIFEXITED()
}

pid_t Fork()
{
    pid_t pid;
    pid=fork();
    if(pid<0)
    {
        fprintf(stderr,"fork error: %s\n",strerror(errno));
    }
    return pid;
}