#include "show_info.h"
//#include <stdio.h>

void show_usage_user() {
    printf("Usage: ./user <acc_ID> <acc_pass> <op_delay_ms> <op_code> <op_args>\n");
    printf("\tacc_ID: 0 - admin ; [1 , %d] - client\n",MAX_BANK_ACCOUNTS);
    printf("\tacc_pass: between 8 and 20 characters long.\n");
    printf("\top_delay_ms: operation delay in miliseconds, 0-%d\n",MAX_OP_DELAY_MS);
    printf("\top_code: %d - OP_CREATE_ACCOUNT; %d - OP_BALANCE; %d - OP_TRANSFER; %d - OP_SHUTDOWN\n",OP_CREATE_ACCOUNT,OP_BALANCE,OP_TRANSFER,OP_SHUTDOWN);
    printf("\top_args: if op_code is %d or %d, op_args = \"\"\n",OP_BALANCE,OP_SHUTDOWN);
    printf("\t\t if op_args is %d then op_args = \"<new_acc_id> <init_balance> <pass>\"\n",OP_CREATE_ACCOUNT);
    printf("\t\t if op_args is %d then op_args = \"<dest_acc_ID> <amount>\"\n",OP_TRANSFER);
}

void show_usage_server() {
    printf("Usage: ./server <nthr> <admin_pass>\n");
    printf("\tnthr: number of threads (e-counters) to be created, 0-%d\n",MAX_BANK_OFFICES);
    printf("\tadmin_pass: between 8 and 20 characters long.\n");
    
}

void show_op_type(op_type_t type) {
    printf("OP type: ");
    switch(type) {
        case OP_CREATE_ACCOUNT:
            printf("CREATE\n");
            break;
        case OP_BALANCE:
            printf("BALANCE\n");
            break;
        case OP_TRANSFER:
            printf("TRANSFER\n");
            break;
        case OP_SHUTDOWN:
            printf("SHUTDOWN\n");
            break;
        default:
            printf("OP INVALID\n");
            break;
    }
}

void show_ret_code(ret_code_t code) {
    printf("Reply return code: ");
    switch(code) {
        case RC_OK:
            printf("OK\n");
            break;
        case RC_SRV_DOWN:
            printf("SRV_DOWN\n");
            break;
        case RC_SRV_TIMEOUT:
            printf("TIMEOUT\n");
            break;
        case RC_USR_DOWN:
            printf("USR_DOWN\n");
            break;
        case RC_LOGIN_FAIL:
            printf("LOGIN_FAIL\n");
            break;
        case RC_OP_NALLOW:
            printf("OP_NALLOW\n");
            break;
        case RC_ID_IN_USE:
            printf("ID IN USE\n");
            break;
        case RC_ID_NOT_FOUND:
            printf("ID_NOT_FOUND\n");
            break;
        case RC_SAME_ID:
            printf("SAME_ID\n");
            break;
        case RC_NO_FUNDS:
            printf("NO_FUNDS\n");
            break;
        case RC_TOO_HIGH:
            printf("TOO_HIGH\n");
            break;
        case RC_OTHER:
            printf("RC_OTHER\n");
            break;
        default:
            printf("RC INVALID\n");
            break;
    }
}

void show_request(tlv_request_t req) {
    printf("///////////////////////////////////////////\n");
    printf("Request report:\n");
    show_op_type(req.type);
    printf("Request length: %d\n",req.length);
    printf("Request pid: %d\n",req.value.header.pid);
    printf("Request account id: %d\n",req.value.header.account_id);
    printf("Request account password: \"%s\"\n",req.value.header.password);
    printf("Request operation delay: %d\n",req.value.header.op_delay_ms);
    if(req.type == OP_CREATE_ACCOUNT) {
        printf("Request Create account id: %d\n",req.value.create.account_id);
        printf("Request Create account balance: %d \n",req.value.create.balance);
        printf("Request Create account password: \"%s\"\n",req.value.create.password);
    }
    else if (req.type == OP_TRANSFER) {
        printf("Request Transfer to account id: %d\n",req.value.transfer.account_id);
        printf("Request Transfer amount: %d\n",req.value.transfer.amount);
    }
    printf("///////////////////////////////////////////\n");
}

void show_reply(tlv_reply_t rep) {
    printf("///////////////////////////////////////////\n");
    printf("Reply report:\n");
    show_op_type(rep.type);
    printf("Reply length: %d\n",rep.length);
    printf("Reply account id: %d\n",rep.value.header.account_id);
    show_ret_code(rep.value.header.ret_code);
    switch (rep.type) {
    case OP_BALANCE:
        printf("Reply balance value: %d\n",rep.value.balance.balance);
        break;
    case OP_TRANSFER:
        printf("Reply transfer balance: %d\n",rep.value.transfer.balance);
        break;
    case OP_SHUTDOWN:
        printf("Reply shutdown active offices: %d\n",rep.value.shutdown.active_offices);
    default:
        break;
    }
    printf("///////////////////////////////////////////\n");
}

void show_account(bank_account_t account) {
    printf("///////////////////////////////////////////\n");    
    printf("Account details:\n");
    printf("Account id: %d\n",account.account_id);
    printf("Account hash: %s\n",account.hash);
    printf("Account salt: %s\n",account.salt);
    printf("Account balance: %d\n",account.balance);
    printf("///////////////////////////////////////////\n");
}
