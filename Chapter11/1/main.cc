#include<unistd.h>
#include<arpa/inet.h>
#include<cstdio>

int main()
{
    char ch[]="172.24.55.103";
    uint32_t num;
    inet_pton(AF_INET,ch,&num);
    // uint32_t
    printf("%x\n",num);
    for(int i=0;i<sizeof(num);++i)
    {
        unsigned char *ch_p=((unsigned char *)(&num))+i;
        printf("%.2x ",*ch_p);
    }
    uint32_t num_transed=ntohl(num);
    printf("%x\n",num_transed);
    char ch_[128];
    inet_ntop(AF_INET,&num,ch_,128);
    printf("%s\n",ch_);
    return 0;
}
