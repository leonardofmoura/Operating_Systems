//PROGRAMA p03.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 10

void * print_tid(void * threadnum) {
    sleep(1);
    printf("Hello from thread with id %lu\n",pthread_self());
    pthread_exit(threadnum);
}

int main() {
    pthread_t threads[NUM_THREADS];

    int t;

    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %d\n",t);
        pthread_create(&threads[t],NULL,print_tid, (void*) &t);
    }

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t],NULL);
    }

    exit(0);
}