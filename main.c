#include <stdio.h>
#include "job.h"

int main(int argc, char* argv[]) {
    int nThreads;

    printf("How many threads do you need?: \n");
    scanf("%d",&nThreads);
    if(delegateWork(nThreads) != 0)
        printf("Errore nella delega ai thread del lavoro");
    return 0;
}