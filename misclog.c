#include "mqtt.h"
#include "utils.h"
#include "globals.h"


int mqtt_online_callback(char *node,char *msg, int len, void *p);


void start_misclog(void *pvt)
{
  char node[255];
    
  sprintf(node,"%s/CHECK",UID);
  mqtt_register_callback(node,&mqtt_online_callback,pvt);
  sprintf(node,"ALL/CHECK");
  mqtt_register_callback(node,&mqtt_online_callback,pvt);
}


int mqtt_online_callback(char *node,char *msg, int len, void *p)
{
    char outnode[128];
    char outString[128];
    int iInput;
 
    iInput = getInteger(msg,len);
 
    sprintf(outString,"%d,ONLINE",iInput);
    sprintf(outnode,"CHECK");
    mqtt_writeresponse(outnode,outString,0);
    
    return 0;
}