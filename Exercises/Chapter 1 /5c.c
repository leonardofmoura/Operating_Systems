#include <stdio.h>
#include <stdlib.h>

//Prints the name of the user using the gentenv() function

int main(int argc, char* agrv[], char* envp[]) {

    printf("Hello %s!\n",getenv("USER"));

    return 0;
}