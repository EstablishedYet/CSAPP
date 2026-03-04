#include<unistd.h>
#include<sys/mman.h>
#include<cstdio>
#include<cstdlib>
#include<csignal>
#include<sys/fcntl.h>
#include<sys/stat.h>

int main(int argc,char **argv)
{
    int fd=open(argv[1],O_RDONLY);
    int offset=atoi(argv[2]);
    // int length=atoi(argv[3]);
    int input_length;
    struct stat buf;
    fstat(fd,&buf);
    int file_length=buf.st_size;
    printf("%d\n",file_length);
    if(offset>file_length)
        offset=0;
    if(argc==4)
    {
        input_length=atoi(argv[3]);
        // if(input_length+offset>file_length)
        //     input_length=file_length-offset;
        input_length=(input_length+offset>file_length)?(file_length-offset):input_length;
    }
    else
    {
        input_length=file_length-offset;
    }
    int pg_offset=offset&~(sysconf(_SC_PAGE_SIZE)-1);
    int overall_length=file_length+offset-pg_offset;
    char *addr=(char *)mmap(NULL,overall_length,PROT_READ,MAP_PRIVATE,fd,pg_offset);
    write(STDOUT_FILENO,addr+offset-pg_offset,file_length);
    close(fd);
    printf("%p %d\n",addr,overall_length);
    munmap(addr,overall_length);
    return 0;
}