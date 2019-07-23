#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

#define READ 0
#define WRITE 1

int main() {

    int pipedes[2];
    pipe(pipedes);

     switch (fork())
     {
        case -1: //error
            return 1;

        case 0: {
            //child process
            int nums[2];
            close(pipedes[WRITE]);
            read(pipedes[READ],nums,2*sizeof(int));
            close(pipedes[READ]);

            int sum = nums[0] + nums[1];
            int diff = nums[0] - nums[1];
            int mult = nums[0] * nums[1];
            if (nums[1] == 0) {
                printf("ERROR unable to divide by zero\n");
            }
            double quo = ((double) nums[0]) / ((double) nums[1]);

            printf("sum : %d\n",sum);
            printf("diff : %d\n",diff);
            printf("mult : %d\n",mult);
            printf("quo : %f\n",quo);
            break;
        } 

        default: { //partent process
            int numbers[2];
            printf(">>>");
            scanf("%d %d",&numbers[0],&numbers[1]);
            close(pipedes[READ]);
            write(pipedes[WRITE],numbers,2*sizeof(int));
            close(pipedes[WRITE]);
        }
     }

    return 0;
}