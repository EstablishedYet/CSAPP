#ifndef MY_MEMLIB_H
#define MY_MEMLIB_H

#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<cerrno>

void heap_init();
void *heap_sbrk(int length);


#endif