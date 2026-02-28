#ifndef SIO_HEADER
#define SIO_HEADER
#include<cstdlib>
#include<cstdio>
#include<cerrno>
#include<cstring>
#include<unistd.h>
#include<csignal>
#include<wait.h>
size_t sio_strlen(char s[]);

void sio_reverse(char s[]);

void sio_ltoa(long v,char s[],int base);

ssize_t sio_puts(char s[]);

ssize_t sio_putl(long v);

void sio_error(char s[]);

void signal_handler1(int sig);

#endif