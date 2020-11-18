#ifndef _E_COUNTER_H_
#define _E_COUNTER_H_

#include "request_queue.h"

typedef struct e_counter {
    int id;
    request_queue_t* request_queue;
} e_counter_t;

void init_e_counters();

void* start_e_counter(void* args);

int create_e_counters(request_queue_t* request_queue, int n_threads);

int wait_for_e_counters();

#endif
