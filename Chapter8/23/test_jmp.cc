#include<unistd.h>
#include<csetjmp>
#include<csignal>
#include<cstdio>
#include<cstdlib>

jmp_buf buf;

int error1=0;
int error2=1;

void test1();
void test2();

int main()
{
    switch(setjmp(buf))
    {
    case 0:
        test1();
        break;
    case 1:
        printf("error1\n");
        break;
    case 2:
        printf("error2\n");
        break;
    default:
        printf("unknown error\n");
    }
    return 0;
}

void test1()
{
    if(error1)
        longjmp(buf,1);
    test2();
    return;
}

void test2()
{
    if(error2)
        longjmp(buf,2);
    return;
}