#ifndef _FILESYSTEMLOG_H
#define _FILESYSTEMLOG_H

#include <pthread.h>
#include <statgrab.h>
#include "mqtt.h"
#include "utils.h"


struct filesystem_log_t {
    pthread_t process_thread;
    int interval;
    void *pvt;
    int thread_tid;
    int stop;
};

volatile struct filesystem_log_t g_filesystemlog;

void start_filesystemlog(struct filesystem_log_t *pvt);



#endif