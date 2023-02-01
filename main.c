#include <stdio.h>
#include "job.h"

int main(int argc, char* argv[]) {
    int nThreads;
    char hostname[100];

    printf("How many threads do you need?: \n");
    scanf("%d",&nThreads);
    printf("Inserisci l' IP: \n");
    scanf("%s",hostname);
    if(delegateWork(nThreads, hostname) != 0)
        printf("Errore nella delega ai thread del lavoro");
    return 0;
}