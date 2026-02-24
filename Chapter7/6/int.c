#include<stdio.h>
#include<malloc.h>
// extern "C" void *malloc(size_t size);
// extern "C" void free(void *ptr);
int main()
{
    int a=1;
    printf("1 %d",a);
    int *p=malloc(32);
    free(p);
    return(0);
}