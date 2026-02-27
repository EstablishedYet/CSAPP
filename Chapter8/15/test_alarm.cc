#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<cerrno>
#include<csignal>

int main()
{
    int secs=alarm(5);
    printf("secs: %d\n",secs);
    sleep(10000);
    return 0;
}