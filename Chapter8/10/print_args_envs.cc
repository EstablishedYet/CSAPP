#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<unistd.h>

extern char **environ;

int main(int argc,char **argv,char **envp)
{
    for(int i=0;i<argc;++i)
    {
        printf("Arg %d: %s\n",i,argv[i]);
    }
    // int ct=0;
    // while(envp[ct])
    // {
    //     printf("Env %d: %s\n",ct++,envp[ct]);
    // }
    for(int i=0;envp[i];++i)
    {
        printf("Env %d: %s\n",i,envp[i]);
    }

    printf("%d\n",setenv("SETENV_TEST","ESTABLISHED",1));
    printf("%p, %p\n",environ,envp);
    // envp--;
    for(int i=0;environ[i];++i)
    {
        printf("Env %d: %s\n",i,environ[i]);
    }
    printf("%p, %p\n",environ,envp);

    return 0;
}