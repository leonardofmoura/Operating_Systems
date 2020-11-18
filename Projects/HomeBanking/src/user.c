//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <errno.h>
//#include <signal.h>
#include <sys/file.h>
//#include <sys/types.h>
#include <sys/stat.h>
//#include <string.h>

#include "logging_user.h"
#include "user_parser.h"
#include "show_info.h"
#include "fail_reply.h"

int main(int argc, char *argv[]) {
    
    if(argc != 6) {
        printf("Wrong number of arguments.\n");
        show_usage_user();
        return FAILURE;
    }

    //parsing request
    int rq;
    tlv_request_t request;
    memset(&request,0,sizeof(tlv_request_t));

    if (input_parser(argv,&request)  != SUCCESS) {
        show_usage_user();
        return FAILURE;
    }
    
    log_request(&request);

    //receive answer from server
    int rs;
    char fifo_path [USER_FIFO_PATH_LEN];
    tlv_reply_t reply;
    memset(&reply,0,sizeof(tlv_reply_t));
    time_t begin;
    
    sprintf(fifo_path,"%s%d",USER_FIFO_PATH_PREFIX,request.value.header.pid);
    if (mkfifo(fifo_path,RDWR_USGR)<0) {
        fail_reply(&reply,&request,RC_OTHER);
        log_reply(&reply);
        //show_reply(reply);
        return FAILURE;
    }

    rq=open(SERVER_FIFO_PATH,O_WRONLY);
    if (rq == -1) {
        fail_reply(&reply,&request,RC_SRV_DOWN);
        log_reply(&reply);
        //show_reply(reply);
        return FAILURE;
    }

    write(rq,&request,sizeof(request));

    
    if ((rs=open(fifo_path,O_RDONLY|O_NONBLOCK)) == -1) {
        fail_reply(&reply,&request,RC_USR_DOWN);
        log_reply(&reply);
        //show_reply(reply);
        return FAILURE;
    }
    
    bool timeout = true;
    time(&begin);
    while(difftime(time(NULL),begin) <= FIFO_TIMEOUT_SECS) {
        if(read(rs,&reply,sizeof(reply)) > 0) {
            log_reply(&reply);
            //show_reply(reply);
            timeout = false;
            break;
        }
    }

    close(rq);
    close(rs);
    
    if(timeout) {
        printf("Timeout on reply.\n");
        fail_reply(&reply,&request,RC_SRV_TIMEOUT);
        log_reply(&reply);
        //show_reply(reply);
        unlink(fifo_path);

        return FAILURE;
    }
    else {

        if(unlink(fifo_path) <0) {
            printf("Error when destroying user channel '%s'\n",fifo_path);
            return FAILURE;
        }
        printf("User channel '%s' has been destroyed\n",fifo_path);
        return SUCCESS;
    }
}