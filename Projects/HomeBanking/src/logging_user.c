#include "logging_user.h"

void log_reply(tlv_reply_t *reply){
    FILE * f = fopen(USER_LOGFILE, "a");
    int fd = fileno(f);

    logReply(fd, getpid(), reply);

    close(fd);
    fclose(f);
}

void log_request(tlv_request_t *request){
    FILE * f = fopen(USER_LOGFILE, "a");
    int fd = fileno(f);

    logRequest(fd, request->value.header.pid, request);
    close(fd);
    fclose(f);
}
