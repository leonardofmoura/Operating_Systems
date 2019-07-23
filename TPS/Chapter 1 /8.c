#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>

//shows the cpu times of the random generation 

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Invalid number of argumets\n");
        return 1;
    }

    struct tms buf;
    srand(time(NULL));
    int random;
    int final = atoi(argv[2]);
    int lim = atoi(argv[1]);
    int i = 0;

    while(random != final) {
        random = rand() % lim;

        printf("[%d] %d\n",i,random);
        i++;
    }

    times(&buf);
    printf("\nReal time: %f\nUser mode:%f\nSystem mode:%f\n",(double) buf.tms_utime/CLOCKS_PER_SEC,(double)buf.tms_cutime/CLOCKS_PER_SEC,(double) buf.tms_cstime/CLOCKS_PER_SEC);
    return 0;
}