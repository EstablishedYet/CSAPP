#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<cerrno>
#include<csignal>
#include<cmath>

// unsigned int snooze(unsigned int secs)
// {

// }
unsigned int all,left;

void my_SIGINT_handler(int sig)
{
    // printf("\nSlept for %d of %d secs.\n",all-left,all);
    // exit(0);
}

int main(int argc,char *argv[])
{
    signal(SIGINT,my_SIGINT_handler);
    char *secs_string=argv[1];
    int secs_number=0;
    int length=strlen(secs_string);
    // while(&secs_string)
    // {
    //     secs_number+=
    // }
    for(int i=0;i<length;++i)
    {
        secs_number+=pow(10,(length-1-i))*(secs_string[i]-'0');
    }
    all=secs_number;
    left=sleep(secs_number);
    printf("\nSlept for %d of %d secs.\n",all-left,all);
    // atoi
    return 0;
}