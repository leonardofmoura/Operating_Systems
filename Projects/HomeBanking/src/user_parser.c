#include "user_parser.h"
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input_parser(char* args[],tlv_request_t *req) {
    req_header_t header;
    memset(&header,0,sizeof(req_header_t));
    req_value_t value;
    memset(&value,0,sizeof(req_value_t));

    if(fill_header(args,&header) != SUCCESS) {
        return  FAILURE;
    }
    
    value.header = header;

    enum op_type type = atoi(args[4]);
    if( type == OP_CREATE_ACCOUNT || type == OP_TRANSFER) {
        
        if(fill_value(args[5],&value,type) != SUCCESS) {
            return FAILURE;
        }
        if(type == OP_CREATE_ACCOUNT) {
            req->length = sizeof(req->value);
        }
        else {
            req->length = sizeof(req->value.header) + sizeof(req->value.transfer);
        }
    }
    else if (type == OP_BALANCE || type == OP_SHUTDOWN) {
        if(strcmp(args[5],"") != 0) {
            printf("This operation takes no arguments.\n");
            return FAILURE;
        }
        req->length = sizeof(req->value.header);
    }
    else {
        printf("Invalid operation request.\n");
        return FAILURE;
    }

    req->type = type;
    req->value = value;
    

    return SUCCESS;
}

int fill_header(char* args[],req_header_t *header) {
    uint32_t acc_id = atoi(args[1]);
    if(acc_id > MAX_BANK_ACCOUNTS) {
        printf("Account ID is invalid\n");
        return FAILURE;
    }

    if(sizeof(args[2]) < MIN_PASSWORD_LEN || sizeof(args[2]) > MAX_PASSWORD_LEN) {
        printf("Password must be between 8 and 20 characters long.\n");
        return FAILURE;
    }

    if(strcmp(strtok(args[2]," "),args[2]) != 0) {
        printf("Password can't contain spaces.\n");
        return FAILURE;
    }

    uint32_t op_delay = atoi(args[3]);

    if(op_delay > MAX_OP_DELAY_MS) {
        printf("Operation delay must be in range: 0 - %d\n",MAX_OP_DELAY_MS);
    }

    header->pid = getpid();
    header->account_id = acc_id;
    sprintf(header->password, "%s", args[2]);
    header->op_delay_ms = op_delay;

    return SUCCESS;
}

int fill_value(char* args,req_value_t *value, op_type_t type) {
    char quant_tok[MAX_BUFFER];
    if(strcmp(args,"") == 0) {
        printf("Operation arguments missing.\n");
        return FAILURE;
    }
    uint32_t acc_id = atoi(strtok(args, " "));
    if(acc_id < 1 || acc_id > MAX_BANK_ACCOUNTS) {
        printf("Account ID in operation is invalid.\n");
        return FAILURE;
    }

    sprintf(quant_tok, "%s", strtok(NULL," "));
        if(strcmp(quant_tok,"") == 0) {
            printf("Missing operation arguments.\n");
            return FAILURE;
    }

    uint32_t quantity = atoi(quant_tok);

    if(quantity < MIN_BALANCE || quantity > MAX_BALANCE) {
            printf("Money quantity must be in range : %ld-%ld\n",MIN_BALANCE,MAX_BALANCE);
            return FAILURE;
    }

    if(type == OP_CREATE_ACCOUNT) {
        value->create.account_id = acc_id;
        value->create.balance = quantity;

        sprintf(value->create.password, "%s", strtok(NULL," "));
        if(strlen(value->create.password) < MIN_PASSWORD_LEN || strlen(value->create.password) > MAX_PASSWORD_LEN) {
            printf("Password must be between 8 and 20 characters long.\n");
            return FAILURE;
        }

        if(strtok(NULL," ") != NULL) {
            printf("Passwords can't contain spaces.\n");
            return FAILURE;
        }
    }
    else {
        value->transfer.account_id = acc_id;
        value->transfer.amount = quantity;

        if(strtok(NULL," ") != NULL) {
            printf("Exceed number of operation arguments.\n");
            return FAILURE;
        }  
    }

    return SUCCESS;
}
