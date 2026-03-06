#include<unistd.h>
#include<cstdio>
#include<fcntl.h>

template<typename T>
void memory_print(void *p)
{
    size_t size=sizeof(T);
    unsigned char *char_p=(unsigned char *)p;
    unsigned char *cur_char_p;
    for(int i=size-1;i>=0;--i)
    {
        cur_char_p=char_p+i;
        // char *content=*cur_char_p;
        printf("%.2x ",*cur_char_p);
    }
}

int main()
{
    // int fd=open("/home/established/CSAPP/Chapter10/1/a.txt",O_WRONLY|O_APPEND,0,S_IRUSR);
    int a=S_IRUSR,b=S_IWUSR;
    printf("%d\n",a);
    memory_print<int>(&b);
    // printf("%d\n",a|b);

    return 0;
}

