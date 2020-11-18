#include "authentication.h"

#define READ    0
#define WRITE   1

void generateSALT(char *salt){
    char hexadecimals[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    char c;

    for(int i = 0; i < HASH_LEN; i++){
        c = hexadecimals[rand() % 16];
        salt[i] = c;
    }
}

void generateHASH(char * salt, char * password,char * result){
    char concatenation[strlen(salt)+strlen(password)+1];

    char result_tmp[HASH_LEN+1] = "";

    sprintf(concatenation,"%s%s", password, salt);

    int pipe1[2];

    if(pipe(pipe1) != 0){
        perror("Failed to open first pipe descriptors\n");  
    }

    int pipe2[2];

    if(pipe(pipe2) != 0){
        perror("Failed to open second pipe descriptors\n");  
    }

    pid_t pid = fork();

    if(pid == 0){
        close(pipe1[WRITE]);
        close(pipe2[READ]);

        dup2(pipe1[READ], STDIN_FILENO);
        dup2(pipe2[WRITE], STDOUT_FILENO);

        execlp("sha256sum", "sha256sum", NULL);
    }
    else{
        close(pipe1[READ]);
        close(pipe2[WRITE]);

        write(pipe1[WRITE], concatenation, strlen(concatenation));

        close(pipe1[WRITE]);

        read(pipe2[READ], result_tmp, HASH_LEN);
    }
    
    snprintf(result,HASH_LEN+1,"%s",result_tmp);
}

bool checkPassword(bank_account_t *bank_account, char * password){
    char tmp[HASH_LEN+1] = "";
    generateHASH(bank_account->salt, password, tmp);
    return (strcmp(tmp,bank_account->hash) == 0);
}

