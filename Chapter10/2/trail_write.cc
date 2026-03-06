#include<unistd.h>
#include<cstdio>
#include<cstdlib>

int main()
{
    char ch[]="ab";
    char *ch_p=ch;
    const char *ch_p_const=ch;
    write(STDOUT_FILENO,ch_p,2);
    exit(0);
}