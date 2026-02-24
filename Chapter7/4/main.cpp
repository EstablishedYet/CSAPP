#include<dlfcn.h>
#include<stdio.h>
// #include<cstdlib>
#include<iostream>
int x[2]={1,2};
int y[2]={2,4};
int z[2]={0,0};

int main()
{
    void *handle;
    
    handle=dlopen("/home/established/CSAPP/Chapter7/3/libvector.so",RTLD_NOW);
    if(!handle)
    {
        std::cerr<<dlerror()<<std::endl;
        std::exit(1);
    }
    void (*addvec)(int *x,int *y,int *z,int n);
    addvec=(void (*)(int *,int *,int *,int))dlsym(handle,"addvec");
    if(dlerror()!=NULL)
    {
        std::cerr<<dlerror()<<std::endl;
        std::exit(1);
    }
    addvec(x,y,z,2);
    std::cout<<z[0]<<z[1]<<std::endl;
    printf("%d %d",z[0],z[1]);
    if(dlclose(handle)<0)
    {
        std::cerr<<dlerror()<<std::endl;
        std::exit(1);
    }
    return 0;
}