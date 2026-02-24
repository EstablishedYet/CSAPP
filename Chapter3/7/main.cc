#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
int main()
{
    string s="/home/amov/log/1.jpg/";
    stringstream ss(s);
    string token;
    vector<string> v;
    while(getline(ss,token,'/'))
    {
        v.push_back(token);
    }
    int i=0;
    // while(!v.empty())
    // {
    //     i+=1;
    //     // cout<<i<<endl;
    //     string cur=v.front();
    //     cout<<cur<<i<<endl;
    //     v.erase(v.begin());
    // }
    for(auto &token:v)
    {
        cout<<token<<endl;
    }
    cout<<"end"<<endl;
    return 0;
}