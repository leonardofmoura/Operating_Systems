#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[]) {
    int i = 0;

    while (envp[i] != 0) {
        printf("%s\n",envp[i]);
        i++;
    }

    return 0;
}