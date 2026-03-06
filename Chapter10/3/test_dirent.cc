#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<cstdio>
#include<cerrno>
#include<cstdlib>
#include<wait.h>

int main()
{
    DIR *d;
    d=opendir("/home/established/CSAPP/Chapter10/3");
    struct dirent *d1;
    errno=0;
    d1=readdir(d);
    while(d1)
    {
        printf("%ld, %s\n",d1->d_ino,d1->d_name);
        d1=readdir(d);
    }
    if(errno!=0)
    {
        fprintf(stderr,"readdir error\n");
        exit(1);
    }
    closedir(d);
    return 0;
    // wait()
}