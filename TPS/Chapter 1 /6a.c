// PROGRAMA p6a.c

//this file includes all the exercises from a) to f)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_LENGTH 256
#define MAX 99

int main(void) 
{
    FILE *src, *dst;
    char buf[BUF_LENGTH];

    if ( ( src = fopen("initfile.txt","r") ) == NULL)
    {
        perror("initfile.txt");
        // printf("initfile.txt: %s\n",strerror(errno)); //this is equivalent to the above line
        // printf("Error %d\n",errno);
        exit(1);
    }
    if ( ( dst = fopen("outfile.txt","w") ) == NULL)
    {
        perror("outfile.txt");
        exit(2);
    }

    while ( ( fgets(buf,MAX, src)) != NULL ) 
    {
        fputs(buf,dst);
    }
    fclose(src);
    fclose(dst);
    exit(0); //zero é geralmente indicativo de sucesso
} 