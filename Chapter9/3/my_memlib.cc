#include"my_memlib.h"

const int MAX_HEAP=20*(1<<20);

static char *heap_base, *heap_brk, *heap_max;

void heap_init()
{
    heap_brk=heap_base=(char *)malloc(MAX_HEAP);
    heap_max=heap_base+MAX_HEAP;
}
// intptr_t
void *heap_sbrk(int length)
{
    char *old_heap_brk=heap_brk;
    if(length<0||(length+heap_brk)>heap_max)
    {
        errno=ENOMEM;
        fprintf(stderr,"heap_sbrk error");
        return (void *)-1;
    }
    heap_brk+=length;
    return (void *)heap_brk;
}

