#include<unistd.h>
#include<arpa/inet.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

int main(int argc,char **argv)
{
    int num=atoi(argv[1]);
    printf("0x%x\n",num);
    struct in_addr a;
    return 0;
}