#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cerrno>
#include<unistd.h>
#include<wait.h>

const int MAXARGS=128;
const int MAXLINE=500;

// extern char **environ;

void eval(char *cmdline);
bool parseline(char *buf,char **argv);
bool builtin_command(char **argv);
void unix_error(const char *comment);

int main()
{
    char cmdline[MAXLINE];
    while(true)
    {
        printf(">");
        fgets(cmdline,MAXLINE,stdin);
        if(!fgets)
        {
            if(feof(stdin))
            {
                exit(0);
            }
            else
            {
                unix_error("Input error");
            }
        }

        eval(cmdline);
    }
}

void unix_error(const char *comment)
{
    printf("%s: %s",comment,strerror(errno));
    return;
}

void eval(char *cmdline)
{
    char buf[MAXLINE];
    strcpy(buf,cmdline);
    pid_t pid;
    int status;
    char *argv[MAXARGS];
    bool if_backboard,if_builtin_command;
    if_backboard=parseline(buf,argv);
    if(!argv[0])
    {
        return;
    }
    if(!builtin_command(argv))
    {
        pid=fork();
        if(pid<0)
        {
            unix_error("fork error");
        }
        if(pid==0)
        {
            int execve_return;
            execve_return=execve(argv[0],argv,environ);
            // if(execve_return<0)
            // {
            //     printf("%s: Command not found.\n",argv[0]);
            //     exit(0);
            // }
            printf("%s: Command not found.\n",argv[0]);
            exit(0);
        }
        else
        {
            if(if_backboard)
            {
                printf("%d, %s",pid,cmdline);
            }
            else
            {
                int waitpid_return;
                waitpid_return=waitpid(pid,&status,0);
                if(waitpid_return<0)
                {
                    unix_error("wait error");
                }
            }
        }
    }
    return;
}

bool parseline(char *buf,char **argv)
{
    char *delimitor;
    int argc=0;
    buf[strlen(buf)-1]=' ';
    while(buf&&(*buf==' '))
    {
        buf++;
    }
    while(delimitor=strchr(buf,' '))
    {
        *delimitor='\0';
        argv[argc++]=buf;
        buf=delimitor+1;
        while(buf&&(*buf==' '))
        {
            buf++;
        }
    }
    argv[argc]=NULL;
    if(argc==0)
    {
        return false;
    }
    if(*argv[argc-1]=='&')
    {
        argc--;
        argv[argc]=NULL;
        return true;
    }
    else
    {
        return false;
    }
}

bool builtin_command(char **argv)
{
    if(!strcmp(argv[0],"quit"))
    {
        exit(0);
    }
    return false;
}