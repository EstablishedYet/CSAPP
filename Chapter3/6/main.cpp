// #include <ros/ros.h>
// // #include <tf/transform_datatypes.h> 
// #include <std_msgs/String.h>
// #include <std_msgs/Float64.h>
// #include <std_msgs/Float32.h>
// #include <std_msgs/Int32.h>
// #include <geometry_msgs/Point.h>
// #include <geometry_msgs/PoseStamped.h>
// #include <nav_msgs/Odometry.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include<filesystem>
using namespace std;
double getCurrentTimeInSeconds()
{
    auto now=chrono::system_clock::now();
    return now.time_since_epoch().count()*1e-6;
}
int main() {
    // 获取当前时间点
    // auto now = std::chrono::high_resolution_clock::now();

    // // 转换为纳秒
    // auto ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    // auto epoch = ns.time_since_epoch();   // 距离 1970-01-01 00:00:00 的时间
    // long long nanoseconds = epoch.count();
    // string a="12";
    // char b=a[0];
    // // cout<<int(a);
    // int x=a.length();
    // cout<<b<<' '<<x;
    // std::cout << "当前时间（纳秒级）: " << nanoseconds << " ns" << std::endl;
    
    // auto seconds=
    string path="/home/amov/buffertest";
    filesystem::remove_all(path);
    filesystem::create_directory(path);

    // cout<<fixed<<seconds*1e-9;
    return 0;
}