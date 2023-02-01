#include "job.h"

typedef struct range{
    int r1;
    int r2;
    int tnum;
    char hostname[100];
} range;

int delegateWork(int numThreads, char* hostname) {
    int* arg;
    range* ra; //lista di range
    ra = (range *) malloc(sizeof(range) * numThreads); //alloco la lista di range nell' heap
    for(int i=0;i<numThreads;i++){ //setto i range di ogni thread
        ra[i].r1 = (65535/numThreads * i) + 1;
        if(i == numThreads - 1)
            ra[i].r2 = 65535;
        else
            ra[i].r2 = 65535/numThreads * (i+1); 
        ra[i].tnum = i+1;
        strcpy(ra[i].hostname, hostname);
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
    portscanner(r.hostname, r.r1, r.r2, r.tnum);
    return NULL;
}

static int portscanner(char* ip, int p1, int p2, int tnum) {
    struct sockaddr_in sa;
    int sock, err;
    strncpy((char*) &sa, "", sizeof sa);
    sa.sin_family = AF_INET; //ipv4
    sa.sin_addr.s_addr = inet_addr(ip); //inserisco ip nella struct
    for(int i=p1;i<=p2;i++)
    {
        sa.sin_port = htons(i);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock<0){
            perror("\nErrore creazione socket");
            exit(1);
        }
        err = connect(sock , (struct sockaddr*)&sa , sizeof sa);
        if( err >= 0 ){
           printf("thread%d --> %-5d open\n", tnum, i);
        }
        close(sock);
    }
    fflush(stdout);
    return 0;
}