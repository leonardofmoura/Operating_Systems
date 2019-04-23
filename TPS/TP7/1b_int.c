//PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2
#define NUMITER 10000


void * thrfunc(void * arg) {
    int i;
    int* num = (int*) arg;

    fprintf(stderr,"Starting thread %d\n", *num);
    for (i = 0; i < NUMITER; i++) write(STDERR,num,1);
    return NULL; 
}

int main() {
    int a = '1';
    int b = '2';

    pthread_t ta,tb;
    
    pthread_create(&ta, NULL, thrfunc, &a);
    //Just to test the use of the same variable for different threads
    // a = '2';
    pthread_create(&tb,NULL,thrfunc,&b); //or &a if testing lines above

    pthread_join(ta,NULL);
    pthread_join(tb,NULL);

    return 0;
}