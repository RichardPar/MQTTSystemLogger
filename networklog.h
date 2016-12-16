#ifndef _NETWORKLOG_H
#define _NETWORKLOG_H

#include <pthread.h>
#include <statgrab.h>
#include "utils.h"

struct network_t {
   int interval;
   pthread_t network_thread;
   int networklog_thread;
   int networklog_stop;
};

struct network_t netinfo;

void start_networklog(struct network_t *net);


#endif