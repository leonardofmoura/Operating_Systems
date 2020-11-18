//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
#include "server_parser.h"
#include "authentication.h"

int input_parser(char* args[],bank_account_t * admin, int* nthr) {
    *nthr = atoi(args[1]);
    char pass[MAX_PASSWORD_LEN+1];

    if(*nthr < 1 || *nthr > MAX_BANK_OFFICES) {
        printf("Number of e-counters must be in range: 1-%d\n",MAX_BANK_OFFICES);
        return FAILURE;
    }

    if(strlen(args[2]) < MIN_PASSWORD_LEN || strlen(args[2]) > MAX_PASSWORD_LEN) {
        printf("Password must be between 8 and 20 characters long.\n");
        return FAILURE;
    }

    sprintf(pass, "%s", strtok(args[2]," "));
    if(strtok(NULL," ") != NULL) {
        printf("Password can't contain spaces.\n");
        return FAILURE;
    }

    admin->account_id = ADMIN_ACCOUNT_ID;
    admin->balance = 0;
    
    generateSALT(admin->salt);
    generateHASH(admin->salt, pass,admin->hash);
    
    return SUCCESS;
}