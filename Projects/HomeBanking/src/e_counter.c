#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "process_request.h"
#include "request_queue.h"
#include "constants.h"
#include "e_counter.h"

bool server_shutdown = false;

static pthread_t e_counters[MAX_BANK_OFFICES];

static pthread_mutex_t e_counter_lock;

int active_e_counters;

void init_e_counters() {
    memset(&e_counters,0,sizeof(e_counters));
    memset(&e_counter_lock,0,sizeof(pthread_mutex_t));
}

void* start_e_counter(void* args) {
    e_counter_t* e_counter_info = (e_counter_t*) args;
    request_queue_t* request_queue = e_counter_info->request_queue;
    int id = e_counter_info->id;

    char fifo_path [USER_FIFO_PATH_LEN];
    int rs;
    tlv_reply_t reply;
    memset(&reply,0,sizeof(tlv_reply_t));

    while (!( server_shutdown && empty_request_queue(request_queue) )) {
        request_queue_wait_for_request(request_queue,id,0);

        pthread_mutex_lock(&e_counter_lock);   
        log_sync(id,SYNC_OP_MUTEX_LOCK,SYNC_ROLE_PRODUCER,0);     

        active_e_counters++;

        if (empty_request_queue(request_queue)) {
            log_sync(id,SYNC_OP_MUTEX_UNLOCK,SYNC_ROLE_PRODUCER,0);
            pthread_mutex_unlock(&e_counter_lock);
            break;
        }

        tlv_request_t request = get_request_queue_front(request_queue);
        request_queue_pop(request_queue,id,request.value.header.pid);

        log_sync(id,SYNC_OP_MUTEX_UNLOCK,SYNC_ROLE_PRODUCER,request.value.header.pid);
        pthread_mutex_unlock(&e_counter_lock);

        sprintf(fifo_path,"%s%d",USER_FIFO_PATH_PREFIX,request.value.header.pid);
        
        time_t begin;
        time(&begin);

        do
        {
            rs = open(fifo_path,O_WRONLY);
            if(rs != -1) {
                break; //failing to communicate with user, continues listening for requests
            }
        } while(difftime(time(NULL),begin) <= FIFO_TIMEOUT_SECS);

        if(rs == -1){
            continue;
        }

        process_request(&request,&reply,id);
        
        write(rs,&reply,sizeof(reply));

        close(rs);

        if (request.type == OP_SHUTDOWN && reply.value.header.ret_code == RC_OK ) {
            server_shutdown = true;
        }
        if (server_shutdown && empty_request_queue(request_queue)) {
            unlock_threads(request_queue);
        }

        log_sync(id,SYNC_OP_MUTEX_LOCK,SYNC_ROLE_PRODUCER,request.value.header.pid);
        pthread_mutex_lock(&e_counter_lock);
        active_e_counters--;
        log_sync(id,SYNC_OP_MUTEX_UNLOCK,SYNC_ROLE_PRODUCER,request.value.header.pid);
        pthread_mutex_unlock(&e_counter_lock);
    }

    free(args);

    log_close_office(id);

    pthread_exit(NULL);
}

int create_e_counters(request_queue_t* request_queue, int n_threads) {
    
    pthread_mutex_init(&e_counter_lock,NULL);

    for (int i = 1; i <= n_threads; i++) {
         e_counter_t* new_e_counter = malloc(sizeof(e_counter_t));
         new_e_counter->id = i;
         new_e_counter->request_queue = request_queue;

        pthread_t tid;

        pthread_create(&tid,NULL,start_e_counter,(void*) new_e_counter);
        log_open_office(i);

        //add the thread to the array to join later
        e_counters[i-1] = tid;
    }

    return 0;
}

int wait_for_e_counters() {
   for (int i = 0; i < MAX_BANK_OFFICES; i++) {
       if (e_counters[i] == 0) {
           break;
       }

        pthread_join(e_counters[i],NULL);
    }

    return 0;
}