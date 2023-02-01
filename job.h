#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>

int delegateWork(int, char*);
static void *workerFunc(void *);
static int portscanner(char*,int,int, int);