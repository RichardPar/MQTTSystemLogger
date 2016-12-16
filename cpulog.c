#include "cpulog.h"
#include <pthread.h>

#include "globals.h"

void* cpu_main(void* ptr);

int mqtt_cpu_callback(char *node,char *msg, int len, void *p)
{
    int iInput;
    struct cpu_log_t *pvt;
    
    pvt = p;
    
    iInput = getInteger(msg,len);

    if ((iInput > 0) && (pvt->cpulog_thread == -1))
    {    
    printf("CPU Logging thread starting\r\n");
    pvt->interval=iInput;   
    pvt->cpulog_thread = pthread_create(&(pvt->cpu_thread), NULL, cpu_main, p);
    if(pvt->cpulog_thread) {
        printf("Error - pthread_create() return code: %d\n", pvt->cpulog_thread);
        return -1;
       }
    } else if ((iInput <= 0) && (pvt->cpulog_thread >= 0))
    {
        pvt->interval=0; 
        pvt->cpulog_stop=1;
    } else {
        pvt->interval=iInput;
    }
        
        
  return 0;  
}

void start_cpulog(struct cpu_log_t *pvt)
{
  char node[255];
    
  pvt->cpulog_thread=-1;
  pvt->cpulog_stop=0;
  
  sprintf(node,"%s/LOG/CPU",UID);
  mqtt_register_callback(node,&mqtt_cpu_callback,pvt);
  sprintf(node,"ALL/LOG/CPU");
  mqtt_register_callback(node,&mqtt_cpu_callback,pvt);
}

void* cpu_main(void* ptr)
{

    sg_cpu_percents* cpu_percent;
    sg_cpu_stats* cpu_diff_stats;
    char outString[120];
    char node[64];
    
    struct cpu_log_t *cpudata;
    cpudata = ptr;
    
    cpu_percent = sg_get_cpu_percents(NULL);

    while(((cpu_diff_stats = sg_get_cpu_stats_diff(NULL)) != NULL) &&
          ((cpu_percent = sg_get_cpu_percents_of(sg_last_diff_cpu_percent, NULL)) != NULL) && (cpudata->cpulog_stop==0)) {

        sg_snapshot();

        sprintf(outString,
                "%d,%3.2f,%3.2f,%3.2f,%3.2f,%3.2f,%3.2f,%llu,%llu,%llu,%llu,%llu,%llu",
                cpudata->interval,
                cpu_percent->user,
                cpu_percent->kernel,
                cpu_percent->iowait,
                cpu_percent->swap,
                cpu_percent->nice,
                cpu_percent->idle,
                cpu_diff_stats->context_switches,
                cpu_diff_stats->voluntary_context_switches,
                cpu_diff_stats->involuntary_context_switches,
                cpu_diff_stats->syscalls,
                cpu_diff_stats->interrupts,
                cpu_diff_stats->soft_interrupts);

        printf("%s\r\n", outString);

        sprintf(node,"LOG/CPU");
        mqtt_writeresponse(node,outString,0);
        
        //sleep(cpudata->interval);
        sleep_with_break(&(cpudata->interval));
    }
    cpudata->cpulog_stop=0;
    cpudata->cpulog_thread = -1;
    pthread_exit(0);
}
