#ifndef ROBUST_IO_H
#define ROBUST_IO_H
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<cerrno>
#include<cstring>

const int RIO_BUFSIZE=8192;

struct rio_t
{
    int rio_fd;
    int rio_cnt;
    char *rio_bufptr;
    char rio_buf[RIO_BUFSIZE];
};

ssize_t rio_readn(int fd,void *buf,size_t n);
ssize_t rio_writen(int fd,void *buf,size_t n);

void rio_readinitb(rio_t *rp,int fd);
ssize_t rio_read(rio_t *rp,void *usrbuf,size_t n);
ssize_t rio_readnb(rio_t *rp,void *buf,size_t n);
ssize_t rio_readlineb(rio_t *rp,void *buf,size_t maxlen);

#endif