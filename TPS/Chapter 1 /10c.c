#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//decomposes a string in tokens and then decomposes those tokens in sub-tokens

#define MAX_STR_LEN 256
#define MAX_TOKENS 99

void token_command(char command[],char* command_array[]) {
    const char delim[] = " ";
    char* token;
    int i = 0;

    token = strtok(command,delim);
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
        printf("%s\n",command_array[k]);
        k++;
    } while (command_array[k] != NULL);
}

int main() {
    char buf[MAX_STR_LEN];
    const char delim1[] = ";|";
    char* token;
    char* command_array[MAX_TOKENS];
    char* token_array[MAX_TOKENS][MAX_TOKENS];
    int i = 0;

    printf("> ");
    fgets(buf,sizeof(buf),stdin);

    //splits all the commands
    token = strtok(buf,delim1);
    command_array[i] = token;
    i++;

    while (token != NULL) {
        token = strtok(NULL,delim1);
        command_array[i] = token;
        i++;
    }

    //splits each command in tokens
    i = 0; 
    while(command_array[i] != NULL){
        token_command(command_array[i],token_array[i]);
        i++;
    }

    return 0;
}