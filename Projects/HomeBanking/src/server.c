#include "server.h"
#include "server_parser.h"
#include "process_request.h"
#include "show_info.h"
#include "request_queue.h"
#include "e_counter.h"
#include <time.h>


extern bool server_shutdown;

static request_queue_t* request_queue;

int receive_requests();

int main (int argc, char *argv []) {
    srand(time(NULL));

    if(argc != 3) {
        printf("Wrong number of arguments.\n");
        show_usage_server();
        return FAILURE;
    }

    //parse input and create admin account
    int nthr;
    bank_account_t* admin = malloc(sizeof(bank_account_t));
    memset(admin,0,sizeof(bank_account_t));

    if(input_parser(argv,admin,&nthr) != SUCCESS) {
        show_usage_server();
        return FAILURE;
    }

    //initalize request queue
    request_queue = request_queue_init(nthr,MAIN_THREAD_ID);

    //create threads (MISSING)
    init_e_counters();
    create_e_counters(request_queue,nthr);

    //logBankOfficeOpen
    //log_open_office(ADMIN_ACCOUNT_ID);

    //load admin into bank accounts
    load_admin(admin);
    
    //log admin account creation 
    log_creat_acc(admin,ADMIN_ACCOUNT_ID);


    if(mkfifo(SERVER_FIFO_PATH,RDWR_USGR) < 0) {
        if(errno==EEXIST) {
            perror(SERVER_FIFO_PATH);
            return FAILURE;
        }
        else
            return FAILURE;
    }

    int rc = receive_requests();

    //after all threads finish processing their requests call this
    clean_accounts();

    if(unlink(SERVER_FIFO_PATH) < 0) {
        printf("Error when destroying secure channel '%s'\n",SERVER_FIFO_PATH);
        return FAILURE;
    }
    else
        printf("Server channel '%s' has been destroyed\n",SERVER_FIFO_PATH);
    
    log_close_office(ADMIN_ACCOUNT_ID);

    request_queue_delete(request_queue);

    return rc;
}

int receive_requests() {

    //receive user requests
    int rq;
    tlv_request_t request;
    int read_status;
    memset(&request,0,sizeof(tlv_request_t));   
    
    do
    {
        
        if((rq = open(SERVER_FIFO_PATH,O_RDONLY)) == -1) {
            continue;
        }

        read_status = read(rq, &request, sizeof(request));
        if(read_status > 0) {
            request_queue_push(request_queue,request,MAIN_THREAD_ID);
        }

        close(rq);
    } while (!(server_shutdown && (read_status == 0)));

    wait_for_e_counters(); 
    
    return SUCCESS;
}