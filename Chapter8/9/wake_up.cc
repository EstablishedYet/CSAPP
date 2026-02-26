#include<unistd.h>
#include<cstdlib>
#include<cstdio>

unsigned int wake_up(int secs)
{
    unsigned int duration=sleep(secs);
    printf("Woke up at %d secs.\n",secs-duration);
    return duration;
}