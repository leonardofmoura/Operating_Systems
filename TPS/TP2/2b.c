#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

//Copies the contects from one file to another 
int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: 2b <source> <destination>\n");
        return 0;
    }

    char c;

    int source = open(argv[1],O_RDONLY);
    int destination = open(argv[2],O_WRONLY);
    int detect = read(source,&c,sizeof(char));
    
    while(detect != 0){
        write(destination,&c,sizeof(char));
        detect = read(source,&c,sizeof(char)); //read returns 0 on eof
    } 

    close(source);
    close(destination);
    
    return 0;
}