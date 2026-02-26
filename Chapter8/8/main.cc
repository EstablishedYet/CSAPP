#include<iostream>
#include<cerrno>
#include<cstring>
#include<unistd.h>
#include<wait.h>
const int N=2;

void unix_error(const char *s);
pid_t Fork();

int main()
{
    int status;
    pid_t pid;
    for(int i=0;i<N;++i)
    {
        pid=Fork();
        if(pid==0)
        {
            exit(100+i);
        }
    }
    while((pid=wait(&status))>0)
    {
        if(WIFEXITED(status))
        {
            printf("Child %d terminated normally with exit status=%d\n",pid,WEXITSTATUS(status));
        }
        else
        {
            printf("Child %d terminated abnormally\n",pid);
        }
    }
    if(errno!=ECHILD)
    {
        unix_error("wait error");
    }
    return 0;
}

void unix_error(const char *s)
{
    fprintf(stderr,"%s: %s\n",s,strerror(errno));
    return;
}

pid_t Fork()
{
    pid_t pid;
    pid=fork();
    if(pid<0)
    {
        unix_error("fork error");
    }
    return pid;
}