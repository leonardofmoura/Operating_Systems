#ifndef _REQUEST_QUEUE_H_
#define _REQUEST_QUEUE_H_

#include "types.h"
#include <semaphore.h>
#include <stdbool.h>

#define SHARED 0

typedef struct node node_t;

struct node{
    tlv_request_t data;       
    node_t* next;       
};

typedef struct {
    node_t* front;      
    node_t* rear;   
    sem_t request_slots;
    sem_t requests_waiting;
    int thread_number;
} request_queue_t;


request_queue_t* request_queue_init(int request_slots, int e_counter_id);


bool empty_request_queue(request_queue_t* queue);


int request_queue_push(request_queue_t* queue, tlv_request_t item, int thread_id);


int request_queue_pop(request_queue_t* queue, int thread_id, int pid);


tlv_request_t get_request_queue_front(request_queue_t* queue);


void request_queue_delete(request_queue_t* queue);


void request_queue_wait_for_request(request_queue_t* queue, int thread_id,int pid);


void unlock_threads(request_queue_t* queue);

#endif
