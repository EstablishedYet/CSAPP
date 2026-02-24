#include<iostream>
#include<map>
using namespace std;
int main()
{
    map<string,map<int,float>> framestorage;
    auto& innermap=framestorage["first"];
    innermap[1]=0.9;
    cout<<framestorage["firs"][1]<<endl;
    return 0;
}