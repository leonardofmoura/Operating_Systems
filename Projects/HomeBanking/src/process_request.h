//#include "sope.h"
//#include <stdlib.h>
//#include <string.h>
#include <sys/stat.h>
#include "authentication.h"
#include "logging_server.h"

void load_admin(bank_account_t* admin);

void process_request(tlv_request_t *request, tlv_reply_t *reply, int id);

void create_account(tlv_request_t *req,tlv_reply_t *rep, int id);

void shutdown(tlv_request_t *request, tlv_reply_t *reply, int id);

void balance(tlv_request_t *request, tlv_reply_t *reply, int id);

void transfer(tlv_request_t *request, tlv_reply_t *reply, int id);

void clean_accounts();