#ifndef _CPULOG_H
#define _CPULOG_H

#include <pthread.h>
#include <statgrab.h>
#include "mqtt.h"
#include "utils.h"


struct cpu_log_t {
    pthread_t cpu_thread;
    int interval;
    void *pvt;
    int cpulog_thread;
    int cpulog_stop;
};

struct cpu_log_t cpulog;

void start_cpulog(struct cpu_log_t *pvt);



#endif