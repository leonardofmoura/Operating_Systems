#include "logging_server.h"
#include <stdio.h>

void log_open_office(int bank_id){
    FILE* f = fopen(SERVER_LOGFILE, "a");
    flockfile(f);
    int fd = fileno(f);
    pthread_t tid = pthread_self();

    logBankOfficeOpen(fd, bank_id, tid);

    funlockfile(f);
    fclose(f);
}

void log_close_office(int bank_id){
    FILE* f = fopen(SERVER_LOGFILE, "a");
    flockfile(f);
    int fd = fileno(f);
    pthread_t tid = pthread_self();

    logBankOfficeClose(fd, bank_id, tid);

    funlockfile(f);
    fclose(f);
}

void log_reply(tlv_reply_t *reply, int bank_id){
    FILE * f = fopen(SERVER_LOGFILE, "a");
    flockfile(f);
    int fd = fileno(f);

    logReply(fd, bank_id, reply);
    
    funlockfile(f);
    fclose(f);
}

void log_request(tlv_request_t *request, int bank_id){
    FILE * f = fopen(SERVER_LOGFILE, "a");
    flockfile(f);
    int fd = fileno(f);

    logRequest(fd, bank_id, request);
    
    funlockfile(f);
    fclose(f);
}

void log_creat_acc(bank_account_t *account, int bank_id) {
    FILE * f = fopen(SERVER_LOGFILE, "a");
    flockfile(f);
    int fd = fileno(f);

    logAccountCreation(fd, bank_id, account);

    funlockfile(f);
    fclose(f);
}

void log_delay(uint32_t op_delay, int bank_id) {
    FILE * f = fopen(SERVER_LOGFILE, "a");
    flockfile(f);
    int fd = fileno(f);

    logDelay(fd, bank_id, op_delay);

    funlockfile(f);
    fclose(f);
}

void log_sync_delay(uint32_t op_delay,int acc_id,int bank_id) {
    FILE * f = fopen(SERVER_LOGFILE, "a");
    flockfile(f);
    int fd = fileno(f);

    logSyncDelay(fd, bank_id, acc_id,op_delay);
    funlockfile(f);
    fclose(f);
}

void log_sync(int thread_id,sync_mech_op_t call_type, sync_role_t role_type, int sid) {
    FILE * f = fopen(SERVER_LOGFILE,"a");
    flockfile(f);
    int fd = fileno(f);

    logSyncMech(fd,thread_id,call_type,role_type,sid);

    funlockfile(f);
    fclose(f);
}

void log_sync_sem(int thread_id,sync_mech_op_t call_type, sync_role_t role_type, int sid, int val) {
    FILE * f = fopen(SERVER_LOGFILE,"a");
    flockfile(f);
    int fd = fileno(f);

    logSyncMechSem(fd,thread_id,call_type,role_type,sid,val);

    funlockfile(f);
    fclose(f);
}