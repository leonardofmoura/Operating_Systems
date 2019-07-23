#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* agrv[], char* envp[]) {

    printf("Hello %s!\n",getenv("USER"));

    return 0;
}