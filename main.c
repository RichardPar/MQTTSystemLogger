#include <stdio.h>
#include <string.h>
#include <statgrab.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include "mqtt.h"
#include "globals.h"
#include "cpulog.h"
#include "netlinklog.h"
#include "networklog.h"
#include "vmlog.h"
#include "filesystemlog.h"
#include "misclog.h"


int main(int argc, char** argv)
{
   int rc;
    
    
    BS = generateBootSession();
    generate_uid(UID);
    
    printf("UID is %s\r\n",UID);
    strcpy(VENDOR,"BT");
    strcpy(PRODUCT,"T2100");
    
    mqtt_initfuncs();
    mqtt_connect(ADDRESS,CLIENTID);


    /* Initialise statgrab */
    //sleep(5);
    sg_init(1);
    sg_snapshot(); // first sample is bogus


    start_cpulog(&cpulog);
    start_vmlog(&vmdata);   
    start_netlinklog(&netlink);
    start_networklog(&netinfo);
    start_filesystemlog(&g_filesystemlog);
    start_smartlog(NULL);
    start_misclog(NULL);
    start_processlog(NULL);

    
 
    while(1) {
        sleep(5);
    }

    sg_shutdown();
    return 0;
}




