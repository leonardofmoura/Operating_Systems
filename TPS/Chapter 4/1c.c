// PROGRAMA p01a.c 
#include <sys/types.h>
#include <stdio.h> 
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 

void sigint_handler(int signo) {   
    printf("In SIGINT handler ...\n"); 
} 
    

int main(void) {
    struct sigaction sa;

    sa.sa_handler = sigint_handler; //specify the handler
    sigfillset(&sa.sa_mask); //block all signals in the handler
    sa.sa_flags = SA_RESTART; //restart any function interrupted
    
    sigaction(SIGINT,&sa,NULL); //install the handler

    printf("Sleeping for 30 seconds ...\n");   
    sleep(30);  
    printf("Waking up ...\n");   
    exit(0); 
}