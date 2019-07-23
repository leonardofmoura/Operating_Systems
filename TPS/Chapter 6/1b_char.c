//PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2
#define NUMITER 10000

void * thrfunc(void * arg) {
    int i;

    fprintf(stderr,"Starting thread %s\n",(char*) arg);
    for (i = 0; i < NUMITER; i++) write(STDERR,arg,1);
    return NULL; 
}

int main() {
    char a = '1';
    char b = '2';

    pthread_t ta,tb;
    
    pthread_create(&ta, NULL, thrfunc, &a);
    pthread_create(&tb,NULL,thrfunc,&b);

    pthread_join(ta,NULL);
    pthread_join(tb,NULL);

    return 0;
}