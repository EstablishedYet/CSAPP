#include<iostream>
int x[2]={1,2};
int add(int *p,int n)
{
    int sum=0;
    for(int i=0;i<n;++i)
    {
        sum+=p[i];
    }
    return sum;
}
int main()
{
    int n=2;
    int sum=add(x,n);
    return 0;
}