#ifdef RUNTIME
#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>
void *malloc(size_t size)
{
    printf("1\n");
    void *(*mallocp)(size_t size);
    // fputs
    char *error;
    mallocp=dlsym(RTLD_NEXT,"malloc");
    if((error=dlerror())!=NULL)
    {
        // std::<<error<<std::endl;
        exit(1);
    }
    char *ptr=mallocp(size);
    // std::cout<<"malloc "<<ptr<<std::endl;
    static int flag=0;
    // if(!flag)
    // {
    //     flag=1;
    //     printf("malloc %p\n",ptr);
    // }
    printf("malloc %p,%d\n",ptr,flag);
    return ptr;
}

void free(void *ptr)
{
    if(!ptr)
    {
        return;
    }
    void (*freep)(void *)=NULL;
    char *error;
    freep=dlsym(RTLD_NEXT,"free");
    if((error=dlerror())!=NULL)
    {
        // std::cerr<<error<<std::endl;
        exit(1);
    }
    freep(ptr);
    static int flag=0;
    // if(!flag)
    // {
    //     flag=1;
    //     printf("free %p\n",ptr);
    // }
    printf("free %p\n",ptr);
    // std::cout<<"free "<<ptr<<std::endl;
}
#endif
