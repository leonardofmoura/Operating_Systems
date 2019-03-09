#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: 3a <source>\n");
        return 0;
    }

    char c;

    int source = open(argv[1],O_RDONLY);
    int detect = read(source,&c,sizeof(char));
    
    while(detect != 0){
        write(STDOUT_FILENO,&c,sizeof(char));
        detect = read(source,&c,sizeof(char)); //read returns 0 on eof
        // printf("%c\n",c);
    } 

    close(source);
    
    return 0;
}