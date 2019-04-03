//PROGRAMA p06_writer.c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    int fd, messagelen, i;
    char message[100];

    do {
        fd = open("/tmp/myfifo",O_WRONLY, O_TRUNC);
        if (fd == -1) sleep(1);
    } while (fd == -1);

    for (i = 1; i <= 3; i++) {
        sprintf(message,"Hello no. %d from process %d\n",i,getpid());
        messagelen = strlen(message+1);
        write(fd,message,messagelen);
        sleep(3);
    }

    close(fd);
    return 0;
}