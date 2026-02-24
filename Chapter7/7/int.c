#include<stdio.h>
#include<malloc.h>
int main()
{
    char *p=malloc(4);
    printf("a,%p",p);
    return 0;
}