
#include <pthread.h>

#include "mqtt.h"
#include "utils.h"
#include "globals.h"
#include "vmlog.h"


void *vm_main(void *ptr);

int mqtt_vm_callback(char *node,char *msg, int len, void *p)
{
   int iInput;    
   struct vmlog_t *vmi;
    
    vmi = p;
    
    printf("MESSAGE : %s (%d)\r\n ",msg,vmi->vmlog_thread);
    
    iInput = getInteger(msg,len);
    
    if ((iInput > 0) && (vmi->vmlog_thread == -1))
    {    
    printf("VM Logging thread starting\r\n");
    vmi->interval=iInput;    
    vmi->vmlog_thread = pthread_create(&(vmi->vm_thread), NULL, vm_main, vmi);
    if(vmi->vmlog_thread) {
        printf("Error - pthread_create() return code: %d\n", vmi->vmlog_thread);
        return 1;
       }
    } else if ((iInput <= 0) && (vmi->vmlog_thread >= 0))
    {
        vmi->interval=0;
        printf("Triggering stop\r\n");
        vmi->vmlog_stop=1;
    } else {
        vmi->interval=iInput;
    }
        
  return 0;  
}




void start_vmlog(struct vmlog_t *p)
{
  char node[255];  
    
    
  struct vmlog_t *vmi;
  vmi = p;
  
    
  vmi->vmlog_thread=-1;
  vmi->vmlog_stop=0;
  
  sprintf(node,"%s/LOG/VM",UID);
  mqtt_register_callback(node,&mqtt_vm_callback,vmi);

  sprintf(node,"ALL/LOG/VM");
  mqtt_register_callback(node,&mqtt_vm_callback,vmi);
  
}


void *vm_main(void *ptr)
{
    sg_mem_stats *mem_stats;
	sg_swap_stats *swap_stats;
    sg_page_stats *page_stats;
    unsigned int pi,po;
    char node[64];

    char outString[120]; 
    struct vmlog_t *vmi;
    
    vmi = ptr;
 

    page_stats = sg_get_page_stats_diff(NULL);
    if (page_stats == NULL)
    {
       vmi->vmlog_stop=0;
       vmi->vmlog_thread = -1;
       pthread_exit(0);
    }

    while (vmi->vmlog_stop==0)
    {
     if( ((mem_stats = sg_get_mem_stats(NULL)) != NULL) &&
	    ((swap_stats = sg_get_swap_stats(NULL)) != NULL))  {
            
        page_stats = sg_get_page_stats_diff(NULL);    
        if (page_stats != NULL)
        {
            pi= page_stats->pages_pagein;
            po=page_stats->pages_pageout;
        } else
        {
            pi=0;
            po=0;
        }    
            
        sprintf(outString,"%d,%llu,%llu,%llu,%llu,%llu,%llu,%llu,%u,%u",vmi->interval,mem_stats->total,mem_stats->used,mem_stats->cache,
                                                                                mem_stats->free,swap_stats->total,swap_stats->used,swap_stats->free,
                                                                                pi,po);    
            
 #if 0           
		printf("Total memory in bytes : %llu\n", mem_stats->total);
		printf("Used memory in bytes : %llu\n", mem_stats->used);
		printf("Cache memory in bytes : %llu\n", mem_stats->cache);
		printf("Free memory in bytes : %llu\n", mem_stats->free);

		printf("Swap total in bytes : %llu\n", swap_stats->total);
		printf("Swap used in bytes : %llu\n", swap_stats->used);
		printf("Swap free in bytes : %llu\n", swap_stats->free);

		total = mem_stats->total + swap_stats->total;
		free = mem_stats->free + swap_stats->free;

		printf("Total VM usage : %5.2f%%\n", 100 - (((float)total/(float)free)));
#endif    

        sprintf(node,"LOG/VM");
        mqtt_writeresponse(node,outString,0);
        sleep_with_break(&(vmi->interval));
	}   
        
    }
    vmi->vmlog_stop=0;
    vmi->vmlog_thread = -1;
    
    
    pthread_exit(0);
}