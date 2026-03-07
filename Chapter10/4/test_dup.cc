#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<cstdio>
// #include<

int main()
{
    int fd=open("/home/established/CSAPP/Chapter10/4/output.txt",O_RDWR|O_APPEND);
    dup2(fd,0);
    dup2(1,7);
    // printf("aaa\n");
    char ch[256];
    scanf("%s",ch);
    // printf("%s",ch);
    write(7,ch,256);
    return 0;
}