#include<iostream>
#include<malloc.h>
extern "C" void *malloc(size_t size);
extern "C" void free(void *ptr);
int main()
{
    int *p=(int *)malloc(32);
    free(p);
    return(0);
}