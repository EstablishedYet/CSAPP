#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<cstdio>

int main()
{
    int fd=open("/home/established/CSAPP/Chapter10/1/",O_RDONLY,0);
    struct stat s;
    fstat(fd,&s);
    const char *type,*permission;
    if(S_ISREG(s.st_mode))
        type="regular";
    else if(S_ISDIR(s.st_mode))
        type="directory";
    else
        type="other";
    if(s.st_mode&S_IRUSR)
        permission="yes";
    else
        permission="no";
    printf("%s, %s",type,permission);
    return 0;
}