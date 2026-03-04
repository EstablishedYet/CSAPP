// #include<cstdlib>
// #include<cstdio>
// #include<cerrno>
// #include<cstring>
// #include<unistd.h>
// #include<csignal>
#include"sio.h"

volatile sig_atomic_t flag;

size_t sio_strlen(const char s[])
{
    size_t l=0;
    while(s[l]!='\0')
    {
        l++;
    }
    return l;
}

void sio_reverse(char s[])
{
    char inter;
    for(int i=0,j=sio_strlen(s)-1;i<j;i++,j--)
    {
        inter=s[i];
        s[i]=s[j];
        s[j]=inter;
    }
    return;
}

void sio_ltoa(long v,char s[],int base)
{
    bool if_neg=false;
    if(v<0)
    {
        if_neg=true;
        v=-v;
    }
    int i=0;
    int cur;
    do
    {
        /* code */
        cur=v%base;
        s[i++]=(cur<10)?cur+'0':cur-10+'a';
    } while ((v/=base)!=0);
    if(if_neg)
        s[i++]='-';
    s[i]='\0';
    sio_reverse(s);
    return;
}

ssize_t sio_puts(const char s[])
{
    return write(STDOUT_FILENO,s,sio_strlen(s));
}

ssize_t sio_putl(long v)
{
    char s[128];
    sio_ltoa(v,s,10);
    return sio_puts(s);
}

void sio_error(const char s[])
{
    write(STDERR_FILENO,s,sio_strlen(s));
    _exit(1);
}

void signal_handler1(int sig)
{
    char s[]="Caught SIGINTa\n";
    sio_puts(s);
    // sio_putl(100);
    // sio_puts(s);
    _exit(0);
}

// int main()
// {
//     signal(SIGINT,signal_handler1);
//     sleep(10);
//     return 0;
// }