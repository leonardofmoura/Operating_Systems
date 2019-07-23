//PROGRAMA p5a.c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int main(void) {
    int fd;
    char* text1 = "AAAAA";
    char* text2 = "BBBBB";

    fd = open("f1.txt",O_CREAT|O_TRUNC|O_WRONLY|O_SYNC,0600);

    if (fd == -1) {
        perror("Error opening file: ");
        return 1;
    }

    getchar();

    if (write(fd,text1,5) == -1) {
        perror("Error writing to file: ");
        return 1;
    }

    getchar();

    if (write(fd,text2,5) == -1) {
        perror("Error writing to file: ");
        return 1;
    }

    if (close(fd) == -1) {
        perror("Error closing file: ");
        return 1;
    }

    return 0;
}
