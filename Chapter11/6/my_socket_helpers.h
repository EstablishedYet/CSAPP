#ifndef MY_SOCKET_HELPER_H
#define MY_SOCKET_HELPER_H

#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>

const int LISTEN_QUE_LEN=1024;
const int MAXLINE=128;

int open_clientfd(char *hostname,char *port);
int open_listenfd(char *port);


#endif