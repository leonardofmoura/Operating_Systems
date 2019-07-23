//this file also includes exercise g)

//writes the contents of argv[1] to argv[2]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_LENGTH 256
#define MAX 99

int main(int argc, char* argv[]) 
{

    if (argc == 1) {
        printf("usage: 6g file1 file2\n");
        exit(3);
    }

    FILE *src, *dst;
    char buf[BUF_LENGTH];

    if ( ( src = fopen(argv[1],"r") ) == NULL)
    {
        perror(argv[1]);
        exit(1);
    }
    if ( ( dst = fopen(argv[2],"w") ) == NULL)
    {
        perror(argv[2]);
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