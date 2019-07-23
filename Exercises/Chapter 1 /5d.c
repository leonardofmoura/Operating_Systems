#include <stdio.h>
#include <stdlib.h>

//Prints the value of the USER_NAME variable

//this assumes the cration of a new environment variable called USER_NAME
//ex: export USER_NAME="Leonardo"

int main(int argc, char* agrv[], char* envp[]) {

    printf("Hello %s!\n",getenv("USER_NAME"));

    return 0;
}