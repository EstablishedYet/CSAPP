#include"my_mm.h"
#include"my_memlib.h"

const int WSIZE=4;
const int DSIZE=8;
const int CHUNKSIZE=(1<<12);

template<typename T>
inline T MAX(T a,T b)
{
    return (a>b)?a:b;
}

// template<typename T>
inline unsigned int PACK(unsigned int size,unsigned int alloc)
{
    return size|alloc;
}

// template<typename T>
inline unsigned int GET(void *p)
{
    return *(unsigned int *)(p);
}

// template<typename T>
inline void PUT(void *p,unsigned int val)
{
    *(unsigned int *)p=val;
}

inline unsigned int GET_SIZE(void *p)
{
    return (*(unsigned int *)p)|~(0x7);
}

inline unsigned int GET_ALLOC(void *p)
{
    return (*(unsigned int *)p)&(0x1);
}

inline void *HDRP(void *bp)
{
    return (char *)bp-WSIZE;
}

inline void *FTRP(void *bp)
{
    return (char *)bp+GET_SIZE(HDRP(bp))-2*WSIZE;
}

inline void *NEXT_BLKP(void *bp)
{
    return (char *)bp+GET_SIZE(HDRP(bp));
}

inline void *PREV_BLKP(void *bp)
{
    return (char *)bp-GET_SIZE((char *)bp-2*WSIZE);
}

inline void ALLOC(void *bp)
{
    *(unsigned int *)HDRP(bp)|=0x1;
    *(unsigned int *)FTRP(bp)|=0x1;
}

inline void FREE(void *bp)
{
    *(unsigned int *)HDRP(bp)&=~0x1;
    *(unsigned int *)FTRP(bp)&=~0x1;
}

inline bool IF_ALLOC(void *bp)
{
    return (*(unsigned int *)HDRP(bp))&0x1;
}

static char *heap_listp;

int mm_init()
{
    if((void *)(heap_listp=(char *)heap_sbrk(4*WSIZE))==(void *)-1)
    {
        return -1;
    }
    PUT(heap_listp,0);
    PUT(heap_listp+WSIZE,PACK(8,1));
    PUT(heap_listp+2*WSIZE,PACK(8,1));
    PUT(heap_listp+3*WSIZE,PACK(0,1));
    heap_listp+=2*WSIZE;
    if(extend_heap(CHUNKSIZE/WSIZE)==NULL)
    {
        return -1;
    }
    return 0;
}

void *extend_heap(size_t words)
{
    char *bp;
    size_t size=((words%2==0)?words:(words+1))*WSIZE;
    if((void *)(bp=(char *)heap_sbrk(size))==(void *)-1)
    {
        return NULL;
    }
    PUT(HDRP(bp),PACK(size,0));
    PUT(FTRP(bp),PACK(size,0));
    PUT(HDRP(NEXT_BLKP(bp)),PACK(0,1));
    return coalesce(bp);
}

void mm_free(void *bp)
{
    // size_t size=GET_SIZE(HDRP(p));
    FREE(bp);
    coalesce(bp);
}

void *coalesce(void *bp)
{
    bool cur_alloc=IF_ALLOC(bp),prev_alloc=IF_ALLOC(PREV_BLKP(bp)),next_alloc=IF_ALLOC(NEXT_BLKP(bp));
    char *prev_bp=(char *)PREV_BLKP(bp),*next_bp=(char *)NEXT_BLKP(bp);
    size_t size;
    if(cur_alloc)
    {
        return bp;
    }
    else
    {
        if(!prev_alloc)
        {
            size=GET_SIZE(HDRP(bp))+GET_SIZE(HDRP(prev_bp));
            PUT(HDRP(prev_bp),PACK(size,0));
            PUT(FTRP(bp),PACK(size,0));
            bp=prev_bp;
        }
        if(!next_alloc)
        {
            size=GET_SIZE(HDRP(bp))+GET_SIZE(HDRP(next_bp));
            PUT(HDRP(bp),PACK(size,0));
            PUT(FTRP(next_bp),PACK(size,0));
            // bp=prev_bp;
        }
    }
    return bp;
}

void *mm_malloc(size_t bytes)
{
    if(bytes<=0)
    {
        return NULL;
    }
    bytes=DSIZE*((bytes+DSIZE+(DSIZE-1))/DSIZE);
    char *bp;
    if((bp=(char *)find_fit(bytes))!=NULL)
    {
        place(bp,bytes);
        return bp;
    }
    int extend_bytes=MAX<int>(bytes,CHUNKSIZE);
    if((bp=(char *)extend_heap(extend_bytes/WSIZE))!=NULL)
    {
        place(bp,bytes);
        return bp;
    }
    return NULL;    
}

void *find_fit(size_t bytes)
{
    char *bp=(char *)NEXT_BLKP(heap_listp);
    while(GET_SIZE(HDRP(bp))!=0)
    {
        if(IF_ALLOC(bp))
        {
            bp=(char *)HDRP(bp);
            continue;
        }
        if(GET_SIZE(HDRP(bp))>=bytes)
            return bp;
    }
    return NULL;
}

void place(void *bp,size_t bytes)
{
    size_t block_size=GET_SIZE(HDRP(bp));
    // if(block_size<bytes)
    //     return NULL;
    PUT(HDRP(bp),PACK(bytes,1));
    // if(block_size==bytes)
    if(block_size<=bytes+2*DSIZE)
    {
        // PUT(HDRP(bp),PACK(bytes,1));
        PUT(FTRP(bp),PACK(bytes,1));
    }
    else
    {
        PUT(FTRP(bp),PACK(block_size-bytes,0));
        PUT(bp+bytes/WSIZE,PACK(bytes,1));
        PUT(bp+bytes/WSIZE+1,PACK(block_size-bytes,0));
    }
}

