//PROGRAMA 5b.c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    int fd;
    char* text1 = "CCCCC";
    char* text2 = "DDDDD";

    fd = open("f1.txt",O_WRONLY|O_SYNC|O_APPEND,0600);

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