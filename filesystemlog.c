#include "filesystemlog.h"
#include <pthread.h>

#include "globals.h"


int mqtt_filesystem_callback(char *node,char *msg, int len, void *p);
void* filesystem_main(void* ptr);


void start_filesystemlog(struct filesystem_log_t *pvt)
{
  char node[255];
    
  pvt->thread_tid=-1;
  pvt->stop=0;
  
  printf("%p \r\n",pvt);
  
  sprintf(node,"%s/LOG/FS",UID);
  mqtt_register_callback(node,&mqtt_filesystem_callback,pvt);
  sprintf(node,"ALL/LOG/FS");
  mqtt_register_callback(node,&mqtt_filesystem_callback,pvt);
}


int mqtt_filesystem_callback(char *node,char *msg, int len, void *p)
{
    int iInput;
    struct filesystem_log_t *pvt;
    
    pvt = p;
  
    printf("Callback %p [%i]\r\n",pvt, pvt->stop);
    
    iInput = getInteger(msg,len);

    if ((iInput > 0) && (pvt->thread_tid == -1))
    {    
    printf("FS Logging thread starting\r\n");
    pvt->interval=iInput;   
    
    pvt->thread_tid = pthread_create(&(pvt->process_thread), NULL, filesystem_main, p);
    if(pvt->thread_tid) {
        printf("Error - pthread_create() return code: %d\n", pvt->thread_tid);
        return -1;
       }
    } else if ((iInput <= 0) && (pvt->thread_tid == 0))
    {
        pvt->interval=0; 
        pvt->stop=1;
    } else if (iInput > 0) {
        pvt->interval=iInput;
    }
        
        
  return 0;  
}

void* filesystem_main(void* ptr)
{

    sg_disk_io_stats *diskio_stats;
	size_t num_diskio_stats;
     char outString[120];
    char node[64];
    struct filesystem_log_t *fsi;
    
    fsi = ptr;
     
    diskio_stats = sg_get_disk_io_stats_diff(&num_diskio_stats);
    while (( (diskio_stats = sg_get_disk_io_stats_diff(&num_diskio_stats)) != NULL) && (fsi->stop == 0)) {
        size_t x;

		qsort(diskio_stats , num_diskio_stats, sizeof(diskio_stats[0]), sg_disk_io_compare_traffic);
        for(x = 0; x < num_diskio_stats; x++){
        
        
        sprintf(outString,
                "%d,%s,%llu,%llu",
                fsi->interval,
                diskio_stats->disk_name,
                diskio_stats->read_bytes,
                diskio_stats->write_bytes);
    
            
        sprintf(node,"LOG/FS");
        
        if ((diskio_stats->read_bytes > 0) || (diskio_stats->write_bytes > 0))
        {   
            mqtt_writeresponse(node,outString,0);    
        }
        
        diskio_stats++;    
        }
        
     sleep_with_break(&(fsi->interval));

    }
    
    printf("Thread exit %p \r\n", diskio_stats);
    fsi->stop=0;
    fsi->thread_tid = -1;
    pthread_exit(0);
    
    
}
