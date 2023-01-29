#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int delegateWork(int);
static void *workerFunc(void *);