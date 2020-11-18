#include "sope.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void log_open_office(int bank_id);
void log_close_office(int bank_id);
void log_reply(tlv_reply_t *reply, int bank_id);
void log_request(tlv_request_t *request, int bank_id);
void log_creat_acc(bank_account_t *account, int bank_id);
void log_delay(uint32_t op_delay, int bank_id);
void log_sync_delay(uint32_t op_delay,int acc_id,int bank_id);
void log_sync(int thread_id,sync_mech_op_t call_type, sync_role_t role_type, int sid);
void log_sync_sem(int thread_id,sync_mech_op_t call_type, sync_role_t role_type, int sid, int val);
