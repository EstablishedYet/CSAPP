#include<stdio.h>

int cond1(int a,int *p)
{
    if(!p)
    {
        goto done;
    }
    if(a<=0)
    {
        goto done;
    }
    *p+=a;
    done:
        return *p;
}

int cond2(int a,int *p)
{
    if(p&&a>0)
        goto if_;
    goto done;
    if_:
        *p+=a;
    done:
        return *p;
}

typedef int row[3];
row A[4];

int main()
{
    // int a=5,b=7;
    // int *p=&b;
    // int c=cond1(a,p);
    // int c_=cond2(a,p);
    // printf("%d",c);
    // printf("%d",c_);
    // printf("%d",sizeof(long double));
    return 0;
}