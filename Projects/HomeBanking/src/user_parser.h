#include "sope.h"

int input_parser(char* args[],tlv_request_t *req);

int fill_header(char* args[],req_header_t *header);

int fill_value(char* args,req_value_t *value, op_type_t type);