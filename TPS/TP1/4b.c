#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    
    if (atoi(argv[argc-1]) == 0) { //check if the last argument is a valid number
        printf("Enter a valid number\n");
        return 1;
    }

    for (int i = atoi(argv[argc-1]); i > 0; i--) {

        printf("Hello ");
        for (int i = 1; i < argc - 1; i++) {
            printf("%s ",argv[i]);
        }
        printf("!\n");

    }

    return 0;
}