#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 256
#define MAX_TOKENS 99

int main() {
    char buf[MAX_STR_LEN];
    const char delim1[] = ";|";
    const char delim2[] = " ";
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

    printf("PLIT 1 \n");
    //splits each command in tokens 
    i = 0;
    int j = 0;
    
    while (command_array[i] != NULL) {
        token = strtok(command_array[i],delim2);
        token_array[i][j] = token;
        j++;
        printf("TOKEN :%s",token);

        while (token != NULL) {
            token = strtok(NULL,delim2);
            token_array[i][j] = token;
            j++;
        } 

        i++;
        printf("ciclo...");
    }

    //print the array
    int k = 0;
    do {
        printf("Array [%d]: %s\n",k,token_array[k]);
        k++;
    } while (token_array[k] != NULL);

    return 0;
}