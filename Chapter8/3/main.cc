#include<iostream>
#include<unistd.h>
#include<string.h>
int main()
{
    FILE *p=fopen("/home/established/CSAPP/Chapter8/3/q.txt","a");
    fprintf(p,"123%d\n",234);
    fclose(p);
    fprint(stderr,"fork error: %s\n",strerror(errno));
    return 0;

}