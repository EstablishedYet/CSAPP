#ifdef COMPILETIME
#include<iostream>
#include<malloc.h>

void *mymalloc(size_t size)
{
    void *ptr=malloc(size);
    std::cout<<"malloc"<<ptr<<std::endl;
    return ptr;
}

void myfree(void *ptr)
{
    free(ptr);
    std::cout<<"free"<<ptr<<std::endl;

}

#endif

#ifdef LINKTIME
#include<iostream>
extern "C" void *__real_malloc(size_t size);
extern "C" void __real_free(void *ptr);

extern "C" void *__wrap_malloc(size_t size)
{
    void *ptr=__real_malloc(size);
    std::cout<<"malloc "<<ptr<<std::endl;
    return ptr;

}

extern "C" void __wrap_free(void *ptr)
{
    __real_free(ptr);
    std::cout<<"free "<<ptr<<std::endl;
}
#endif

#ifdef RUNTIME
// #define _GNU_SOURCE
#include<iostream>
#include<dlfcn.h>
extern "C" void *malloc(size_t size)
{
    void *(*mallocp)(size_t size);
    // fputs
    char *error;
    mallocp=(void *(*)(size_t))dlsym(RTLD_NEXT,"malloc");
    if((error=dlerror())!=NULL)
    {
        std::cerr<<error<<std::endl;
        std::exit(1);
    }
    void *ptr=mallocp(size);
    std::cout<<"malloc "<<ptr<<std::endl;
    return ptr;
}

extern "C" void free(void *ptr)
{
    void (*freep)(void *);
    char *error;
    freep=(void (*)(void *))dlsym(RTLD_NEXT,"free");
    if((error=dlerror())!=NULL)
    {
        std::cerr<<error<<std::endl;
        std::exit(1);
    }
    freep(ptr);
    std::cout<<"free "<<ptr<<std::endl;
}
#endif
