#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 256
#define MAX_TOKENS 99

int main() {
    char buf[MAX_STR_LEN];
    const char delim[] = " ";
    char* token;
    char* command_array[MAX_TOKENS];
    int i = 0;

    printf("> ");
    fgets(buf,sizeof(buf),stdin);

    token = strtok(buf,delim);
    command_array[i] = token;
    i++;

    while (token != NULL) {
        token = strtok(NULL,delim);
        command_array[i] = token;
        i++;
    }

    //test if the array is being filled
    int k = 0;
    do {
        printf("Array [%d]: %s\n",k,command_array[k]);
        k++;
    } while (command_array[k] != NULL);

    return 0;
}