#include "fail_reply.h"
#include <stdio.h>

void fail_reply(tlv_reply_t * rep, tlv_request_t *req, ret_code_t rc) {
    rep->type = req->type;
    rep->value.header.account_id = req->value.header.account_id;
    rep->value.header.ret_code = rc;
    rep->length = sizeof(rep->value.header);
    
    switch(req->type) {
        case OP_CREATE_ACCOUNT:
            rep->length = sizeof(rep->value.header);
            break;
        case OP_BALANCE:
            rep->value.balance.balance = 0; //error value
            break;
        case OP_TRANSFER:
            rep->value.transfer.balance = req->value.transfer.amount; //error value
            break;
        case OP_SHUTDOWN:
            rep->value.shutdown.active_offices = 0; //error value
            break;
        default:
            //do nothing
            break;
    }
}