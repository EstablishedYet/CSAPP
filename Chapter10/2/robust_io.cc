#include"robust_io.h"

void unix_error(const char *msg)
{
    fprintf(stderr,"%s\n",msg);
    exit(1);
}

ssize_t rio_readn(int fd,void *buf,size_t n)
{
    size_t nleft=n;
    ssize_t nread;
    char *buf_p=(char *)buf;
    while(nleft>0)
    {
        if((nread=read(fd,buf_p,nleft))<0)
        {
            if(errno==EINTR)
                nread=0;
            else
                return -1;
        }
        else
        {
            if(nread==0)
                break;
        }
        buf_p+=nread;
        nleft-=nread;
    }
    return n-nleft;
}

ssize_t rio_writen(int fd,void *buf,size_t n)
{
    const char *buf_p=(const char *)buf;
    ssize_t nwrite;
    size_t nleft=n;
    while(nleft>0)
    {
        if((nwrite=write(fd,buf_p,nleft))<0)
        {
            if(errno=EINTR)
            {
                nwrite=0;
            }
            else
            {
                return -1;
            }
        }
        // else
        // {
        //     if(nread==0)
        //     {
        //         break;
        //     }
        // }
        buf_p+=nwrite;
        nleft-=nwrite;
    }
    return n-nleft;
}

void rio_readinitb(rio_t *rp,int fd)
{
    rp->rio_fd=fd;
    rp->rio_cnt=0;
    rp->rio_bufptr=rp->rio_buf;
}


ssize_t rio_read(rio_t *rp,void *usrbuf,size_t n)
{
    while(rp->rio_cnt==0)
    {
        rp->rio_cnt=read(rp->rio_fd,rp->rio_buf,sizeof(rp->rio_buf));
        if(rp->rio_cnt<0)
        {
            if(errno!=EINTR)
                return -1;
        }
        else
        {
            if(rp->rio_cnt==0)
                return 0;
            else
            {
                rp->rio_bufptr=rp->rio_buf;
            }
        }
    }
    n=(n>rp->rio_cnt)?rp->rio_cnt:n;
    memcpy(usrbuf,rp->rio_bufptr,n);
    rp->rio_cnt-=n;
    rp->rio_bufptr+=n;
    return n;
}

ssize_t rio_readnb(rio_t *rp,void *buf,size_t n)
{
    // rio_t rio;
    // rio_readinitb(&rio,fd);
    ssize_t nleft=n,nread;
    char *buf_p=(char *)buf;
    while(nleft>0)
    {
        if((nread=rio_read(rp,buf_p,nleft))<0)
        {
            return -1;
        }
        else
        {
            if(nread==0)
            {
                break;
            }
        }
        nleft-=nread;
        buf_p+=nread;
    }
    return n-nleft;
}

ssize_t rio_readlineb(rio_t *rp,void *buf,size_t maxlen)
{
    size_t leftlen=maxlen,byteread;
    char *buf_p=(char *)buf;
    char ch;
    while(leftlen>1)
    {
        if((byteread=rio_read(rp,&ch,1))<0)
        {
            return -1;
        }
        else
        {
            
            if(byteread==0)
            {
                if(leftlen==maxlen)
                {
                    return 0;
                }
                // return 0;
                break;
            }
        }
        // ch=*buf_p;
        *buf_p=ch;
        
        if(*buf_p=='\n')
        {
            buf_p+=byteread;
            leftlen-=byteread;
            break;
        }
        buf_p+=byteread;
        leftlen-=byteread;
    }
    *(buf_p)=0;
    // leftlen--;
    return maxlen-leftlen;
}

ssize_t Rio_readn(int fd,void *buf,size_t n)
{
    ssize_t rc;
    if((rc=rio_readn(fd,buf,n))<0)
    {
        unix_error("rio_readn error");
    }
    return rc;
}
ssize_t Rio_writen(int fd,void *buf,size_t n)
{
    ssize_t rc;
    if((rc=rio_writen(fd,buf,n))<0)
    {
        unix_error("rio_writen error");
    }
    return rc;
}
// ssize_t Rio_read(rio_t *rp,void *usrbuf,size_t n);
ssize_t Rio_readnb(rio_t *rp,void *buf,size_t n)
{
    ssize_t rc;
    if((rc=rio_readnb(rp,buf,n))<0)
    {
        unix_error("rio_readnb error");
    }
    return rc;
}
ssize_t Rio_readlineb(rio_t *rp,void *buf,size_t maxlen)
{
    ssize_t rc;
    if((rc=rio_readlineb(rp,buf,maxlen))<0)
    {
        unix_error("rio_readlineb error");
    }
    return rc;
}
