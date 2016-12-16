#include "globals.h"
#include "networklog.h"

void* network_main(void* ptr);

int mqtt_network_callback(char *node,char *msg, int len, void *p)
{
    int iInput;
    struct network_t *ni;
    
    ni=p;
    
    
    iInput = getInteger(msg,len);

    if ((iInput > 0) && (ni->networklog_thread == -1))
    {    
    printf("Network Logging thread starting\r\n");
    ni->interval=iInput;   
    ni->networklog_thread = pthread_create(&(ni->network_thread), NULL, network_main,ni);
    if(ni->networklog_thread) {
        printf("Error - pthread_create() return code: %d\n", ni->networklog_thread);
        return;
       }
    } else if ((iInput <= 0) && (ni->networklog_thread >= 0))
    {
        ni->interval=0;
        ni->networklog_stop=1;
    } else 
    {
        ni->interval=iInput; 
    }
        
  return 1;  
}


void start_networklog(struct network_t *p)
{
  char node[255];  
    
  struct network_t *ni;  
    
  ni = p;  
  ni->networklog_thread=-1;
  ni->networklog_stop=0;
  
  sprintf(node,"%s/LOG/NETWORK",UID);
  mqtt_register_callback(node,&mqtt_network_callback,ni);
  
  sprintf(node,"ALL/LOG/NETWORK");
  mqtt_register_callback(node,&mqtt_network_callback,ni);
  
}

void* network_main(void* ptr)
{
   	sg_network_io_stats *network_stats;
	size_t num_network_stats;
    char outString[255];
    char node[64];
    size_t x;
    
    struct network_t *ni;
    
    ni=ptr;
    
    network_stats = sg_get_network_io_stats_diff(&num_network_stats);
       
    while ( (network_stats = sg_get_network_io_stats_diff(&num_network_stats))  && (ni->networklog_stop==0) != NULL)
        {
        for(x = 0; x < num_network_stats; x++){
          if (!strncmp(network_stats->interface_name,"lo",2))
          {
              network_stats++;
              continue;
          }
            
         sprintf(outString,
                "%d,%s,%llu,%llu,%llu,%llu,%llu,%llu,%llu",
                ni->interval,
                network_stats->interface_name,
                network_stats->rx,
                network_stats->tx,
                network_stats->ipackets,
                network_stats->opackets,
                network_stats->ierrors,
                network_stats->oerrors,
                network_stats->collisions);
                
                sprintf(node,"LOG/NETWORK");
                mqtt_writeresponse(node,outString,0);
        
        network_stats++;
        }                
            
          sleep_with_break(&(ni->interval));  
          //sleep(ni->interval);
        }
 
    ni->networklog_stop=0;
    ni->networklog_thread = -1;
    pthread_exit(0);
   
}
