#include "job.h"

typedef struct range{
    int r1;
    int r2;
} range;

int delegateWork(int numThreads) {
    int* arg;
    range* ra; //lista di range
    ra = (range *) malloc(sizeof(range) * numThreads); //alloco la lista di range nell' heap
    for(int i=0;i<numThreads;i++){ //setto i range di ogni thread
        ra[i].r1 = (65535/numThreads * i) + 1;
        if(i == numThreads - 1)
            ra[i].r2 = 65535;
        else
            ra[i].r2 = 65535/numThreads * (i+1); 
    }
    pthread_t *ptrThread; //lista di pthread
    ptrThread = (pthread_t *) malloc(sizeof(pthread_t) * numThreads); //alloco la lista di pthread nell' heap
    for(int i=0;i<numThreads;i++) //mando in esecuzione i thread
        pthread_create(&ptrThread[i], NULL, workerFunc, (void*) ra + (i * sizeof(range))); 
    for(int i=0;i<numThreads;i++) //aspetto che tutti i thread abbiano finito
        pthread_join(ptrThread[i], (void **) arg);
    return 0;
}

static void* workerFunc(void * arg){
    range r = * (range *) arg;
    printf("--------------------\n");
    printf("r1: %d\nr2: %d\n", r.r1, r.r2);
    return NULL;
}