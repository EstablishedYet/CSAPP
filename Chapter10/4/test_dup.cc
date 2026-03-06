#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<cstdio>
// #include<

int main()
{
    int fd=open("/home/established/CSAPP/Chapter10/4/output.txt",O_RDWR|O_APPEND);
    dup2(fd,0);
    // printf("aaa\n");
    char ch[256];
    scanf("%s",ch);
    printf("%s",ch);
    return 0;
}