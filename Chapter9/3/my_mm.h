#ifndef MY_MM_H
#define MY_MM_H

#include<unistd.h>
#include<cstdlib>
#include<cstdio>
#include<cerrno>

int mm_init();
void *extend_heap(size_t words);
void *coalesce(void *p);
void mm_free(void *p);
void *mm_malloc(size_t bytes);
void *find_fit(size_t bytes);
void place(void *p,size_t bytes);
#endif