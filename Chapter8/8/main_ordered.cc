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
    pid_t pid_list[N];
    for(int i=0;i<N;++i)
    {
        pid=Fork();
        if(pid==0)
        {
            exit(100+i);
        }
        else
        {
            pid_list[i]=pid;
        }
    }
    int i=0;
    // while((pid=wait(&status))>0)
    while(true)
    {
        printf("%d\n",pid_list[i]);
        pid_t cur_pid=waitpid(pid_list[i++],&status,0);
        printf("%d\n",cur_pid);
        // (pid=)>0
        if(cur_pid>0)
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
        else
        {
            break;
        }
    }
    if(errno!=ECHILD)
    {
        printf("no\n");
        unix_error("wait error");
    }
    else
    {
        printf("yes\n");
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