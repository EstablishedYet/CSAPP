#include<iostream>
using namespace std;
int Add(int n)
{
    cout<<1<<endl;
    return n+1;
}
int main()
{
    int i=0,a=0;
    for(;i<=5;++i)
    {
        // cout<<1<<endl;
        Add(a);
    }
    return 0;
} // namespace std
