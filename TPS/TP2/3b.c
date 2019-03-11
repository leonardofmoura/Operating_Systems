#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: 3a <source> [destination]\n");
        return 0;
    }

    char c;

    int source = open(argv[1],O_RDONLY);
    int detect = read(source,&c,sizeof(char));

    if (argc == 3) {
        int destinaion = open(argv[2],O_WRONLY);
        dup2(destinaion,STDOUT_FILENO);
    }
    
    while(detect != 0){
        write(STDOUT_FILENO,&c,sizeof(char));
        detect = read(source,&c,sizeof(char)); //read returns 0 on eof
    } 

    close(source);
    
    return 0;
}