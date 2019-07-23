//PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define STDERR 2
#define TOTALCHARS 50000

int count = 0;

void * thrfunc(void * arg) {
    int i;
    int* writen_chars_ptr = (int*) malloc(sizeof(int));
    int writen_chars = 0;

    fprintf(stderr,"Starting thread %s\n",(char*) arg);
    while(count < TOTALCHARS)  {
        writen_chars++;
        count++;
        fprintf(stderr,"%d -> %s\n",count,(char*) arg);
    }

    *writen_chars_ptr = writen_chars;

    return writen_chars_ptr;
}

int main() {
    pthread_t ta,tb;
    int* ret1;
    int* ret2;
    
    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb,NULL,thrfunc,"2");

    pthread_join(ta,(void*) &ret1);
    pthread_join(tb,(void*) &ret2);

    if (*ret1 + *ret2 == TOTALCHARS) {
        printf("Success!\n");
    }
    else {
        printf("It failed :(\n");
    }

    printf("%d   %d -> %d\n",*ret1,*ret2,*ret1 + *ret2);

    free(ret1);
    free(ret2);

    return 0;
}