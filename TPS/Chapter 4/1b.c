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
    signal(SIGINT,SIG_IGN);

    printf("Sleeping for 30 seconds ...\n");   
    sleep(30);  
    printf("Waking up ...\n");   
    exit(0); 
}