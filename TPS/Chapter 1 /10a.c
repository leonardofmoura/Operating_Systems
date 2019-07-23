#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 256

int main() {
    char buf[MAX_STR_LEN];
    const char delim[] = " ";
    char* token;

    printf("> ");
    fgets(buf,sizeof(buf),stdin);

    token = strtok(buf,delim);

    while (token != NULL) {
        printf("%s\n",token);

        token = strtok(NULL,delim);
    }

    return 0;
}