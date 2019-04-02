#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

#define READ 0
#define WRITE 1

struct nums {
    int first;
    int second;
};

int main() {

    int pipedes[2];
    pipe(pipedes);

     switch (fork())
     {
        case -1: //error
            return 1;

        case 0: {
            //child process
            struct nums nu;
            close(pipedes[WRITE]);
            read(pipedes[READ],&nu,sizeof(nu));
            close(pipedes[READ]);

            int sum = nu.first + nu.second;
            int diff = nu.first - nu.second;
            int mult = nu.first * nu.second;
            if (nu.second == 0) {
                printf("ERROR unable to divide by zero\n");
            }
            double quo = ((double) nu.first) / ((double) nu.second);

            printf("sum : %d\n",sum);
            printf("diff : %d\n",diff);
            printf("mult : %d\n",mult);
            printf("quo : %f\n",quo);
            break;
        } 

        default: { //partent process
            struct nums n;
            printf(">>>");
            scanf("%d %d",&n.first,&n.second);
            close(pipedes[READ]);
            write(pipedes[WRITE],&n,sizeof(n));
            close(pipedes[WRITE]);
        }
     }

    return 0;
}