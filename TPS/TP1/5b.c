#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[], char* envp[]) {
    char user[] = "USER"; 

    int i = 0;

    while (envp[i] != 0) {
        if (strncmp(user,envp[i],4) == 0) {
            printf("Hello %s!\n",envp[i] + 5);
            break;
        }
        i++;
    }

    return 0;
}