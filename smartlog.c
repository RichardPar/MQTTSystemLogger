#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>

#include "globals.h"
#include "atasmart.h"
#include "smartlog.h"


#ifndef STRPOOL
#define _P(x) x
#endif

const char *disk_type_to_human_string(SkDiskType type);
const char *disk_type_to_prefix_string(SkDiskType type);
static SkBool smart_is_available(SkDisk *d);
static const char *yes_no(SkBool b);
void dump_attributes(SkDisk *d, const SkSmartAttributeParsedData *a, void* userdata);
char *print_values(char *s, size_t len, uint64_t pretty_value, SkSmartAttributeUnit pretty_unit);
char* print_names(char *s, size_t len, uint8_t id, const char *k);
int mqtt_smart_callback(char *node,char *msg, int len, void *p);



void start_smartlog(void *pvt)
{
  char node[255];
    
  sprintf(node,"%s/LOG/SMART",UID);
  mqtt_register_callback(node,&mqtt_smart_callback,pvt);
  sprintf(node,"ALL/LOG/SMART");
  mqtt_register_callback(node,&mqtt_smart_callback,pvt);
}

int mqtt_smart_callback(char *node,char *msg, int len, void *p)
{
    char inMessage[128];
    
    memcpy(inMessage,msg,len);
    inMessage[len]=0;
    
    do_smarttest(inMessage);
    
}


int smart_dump(SkDisk *d) {
        int ret;
        SkBool awake = FALSE;
        char node[128];
        char outString[1024];
        uint64_t size;

        sprintf(outString,"%s,%s%s%s,%s",
               d->name,
               d->name ? disk_type_to_prefix_string(d->type) : "",
               d->name ? ":" : "",
               d->name ? d->name : "n/a",
               disk_type_to_human_string(d->type));

        sprintf(node,"LOG/SMART/DEVICE");
        mqtt_writeresponse(node,outString,0);
        
        
        ret = sk_disk_get_size(d, &size);
        if (ret >= 0)
                sprintf(outString,"%s,%lu,MiB", d->name,(unsigned long) (d->size/1024/1024));
        else
                sprintf(outString,"%s,UNKNOWN,MiB",d->name,strerror(errno));

        sprintf(node,"LOG/SMART/SIZE");
        mqtt_writeresponse(node,outString,0);
        
                if (d->identify_valid) {
                const SkIdentifyParsedData *ipd;
                unsigned i;

                if ((ret = sk_disk_identify_parse(d, &ipd)) < 0)
                        return ret;

                sprintf(outString,"%s,%s,"
                       "%s,"
                       "%s,"
                       "%s",
                       d->name,
                       ipd->model,
                       ipd->serial,
                       ipd->firmware,
                       yes_no(smart_is_available(d)));

            sprintf(node,"LOG/SMART/IDENTIFY");
            mqtt_writeresponse(node,outString,0);        
        }

      if (smart_is_available(d)) {
          SkBool good;
          
          
          if ((ret = sk_disk_smart_read_data(d)) < 0)
                        return -1;

          ret = sk_disk_smart_status(d, &good);
          if (ret >= 0)
          {
              
          if (!good)
                  sprintf(outString,"%s,FAIL",d->name);
          else    
                  sprintf(outString,"%s,PASS",d->name);
         
           sprintf(node,"LOG/SMART/HEALTH");
           mqtt_writeresponse(node,outString,0); 
          }

         ret = sk_disk_smart_parse_attributes(d, dump_attributes,d);
         printf("Ret is %d\r\n",ret);
 
 
        
      }  // end of SMART avaliable clause


}
    
void dump_attributes(SkDisk *d, const SkSmartAttributeParsedData *a, void* userdata) {
        char name[32];
        char pretty[32];
        char node[128];
        char outString[1024];
        
        
        
        sprintf(outString,"%s,%d,%s,%s",
              d->name,
              a->id,
              print_names(name, sizeof(name), a->id, a->name),
              print_values(pretty, sizeof(pretty), a->pretty_value, a->pretty_unit));
               
        sprintf(node,"LOG/SMART/%s",print_names(name, sizeof(name), a->id, a->name));
           mqtt_writeresponse(node,outString,0);

    return;
}
    
    

int do_smarttest(char *device)
{
    int rc;
    SkDisk *d;
      
    
    
    rc = sk_disk_open(device, &d); 
     
    if (rc < 0)
    {
        fprintf(stderr, "Failed to open disk %s: %s\n", device, strerror(errno));
        return -1;
    }
    
    
    smart_dump(d);
    
    if (d)
        sk_disk_free(d);

    
    
    return 0;
}



const char *disk_type_to_human_string(SkDiskType type) {

        /* %STRINGPOOLSTART% */
        static const char* const map[_SK_DISK_TYPE_MAX] = {
                [SK_DISK_TYPE_ATA_PASSTHROUGH_16] = "16 Byte SCSI ATA SAT Passthru",
                [SK_DISK_TYPE_ATA_PASSTHROUGH_12] = "12 Byte SCSI ATA SAT Passthru",
                [SK_DISK_TYPE_LINUX_IDE] = "Native Linux IDE",
                [SK_DISK_TYPE_SUNPLUS] = "Sunplus SCSI ATA Passthru",
                [SK_DISK_TYPE_JMICRON] = "JMicron SCSI ATA Passthru",
                [SK_DISK_TYPE_BLOB] = "Blob",
                [SK_DISK_TYPE_AUTO] = "Automatic",
                [SK_DISK_TYPE_NONE] = "None"
        };
        /* %STRINGPOOLSTOP% */

        if (type >= _SK_DISK_TYPE_MAX)
                return NULL;

        return _P(map[type]);
}

const char *disk_type_to_prefix_string(SkDiskType type) {

        /* %STRINGPOOLSTART% */
        static const char* const map[_SK_DISK_TYPE_MAX] = {
                [SK_DISK_TYPE_ATA_PASSTHROUGH_16] = "sat16",
                [SK_DISK_TYPE_ATA_PASSTHROUGH_12] = "sat12",
                [SK_DISK_TYPE_LINUX_IDE] = "linux-ide",
                [SK_DISK_TYPE_SUNPLUS] = "sunplus",
                [SK_DISK_TYPE_JMICRON] = "jmicron",
                [SK_DISK_TYPE_NONE] = "none",
                [SK_DISK_TYPE_AUTO] = "auto",
        };
        /* %STRINGPOOLSTOP% */

        if (type >= _SK_DISK_TYPE_MAX)
                return NULL;

        return _P(map[type]);
}

static SkBool smart_is_available(SkDisk *d) {
        return d->identify_valid && !!(d->identify[164] & 1);
}


static const char *yes_no(SkBool b) {
        return  b ? "yes" : "no";
}

char *print_values(char *s, size_t len, uint64_t pretty_value, SkSmartAttributeUnit pretty_unit) {

        switch (pretty_unit) {
                case SK_SMART_ATTRIBUTE_UNIT_MSECONDS:

                        if (pretty_value >= 1000LLU*60LLU*60LLU*24LLU*365LLU)
                                snprintf(s, len, "%0.1f,years", ((double) pretty_value)/(1000.0*60*60*24*365));
                        else if (pretty_value >= 1000LLU*60LLU*60LLU*24LLU*30LLU)
                                snprintf(s, len, "%0.1f,months", ((double) pretty_value)/(1000.0*60*60*24*30));
                        else if (pretty_value >= 1000LLU*60LLU*60LLU*24LLU)
                                snprintf(s, len, "%0.1f,days", ((double) pretty_value)/(1000.0*60*60*24));
                        else if (pretty_value >= 1000LLU*60LLU*60LLU)
                                snprintf(s, len, "%0.1f,h", ((double) pretty_value)/(1000.0*60*60));
                        else if (pretty_value >= 1000LLU*60LLU)
                                snprintf(s, len, "%0.1f,min", ((double) pretty_value)/(1000.0*60));
                        else if (pretty_value >= 1000LLU)
                                snprintf(s, len, "%0.1f,s", ((double) pretty_value)/(1000.0));
                        else
                                snprintf(s, len, "%llu,ms", (unsigned long long) pretty_value);

                        break;

                case SK_SMART_ATTRIBUTE_UNIT_MKELVIN:
                        snprintf(s, len, "%0.1f,C", ((double) pretty_value - 273150) / 1000);
                        break;

                case SK_SMART_ATTRIBUTE_UNIT_SECTORS:
                        snprintf(s, len, "%llu,sectors", (unsigned long long) pretty_value);
                        break;

                case SK_SMART_ATTRIBUTE_UNIT_PERCENT:
                        snprintf(s, len, "%llu,%%", (unsigned long long) pretty_value);
                        break;

                case SK_SMART_ATTRIBUTE_UNIT_SMALL_PERCENT:
                        snprintf(s, len, "%0.3f,%%", (double) pretty_value);
                        break;

                case SK_SMART_ATTRIBUTE_UNIT_MB:
                        if (pretty_value >= 1000000LLU)
                          snprintf(s, len, "%0.3f,TB",  (double) pretty_value / 1000000LLU);
                        else if (pretty_value >= 1000LLU)
                          snprintf(s, len, "%0.3f,GB",  (double) pretty_value / 1000LLU);
                        else
                          snprintf(s, len, "%llu,MB", (unsigned long long) pretty_value);
                        break;

                case SK_SMART_ATTRIBUTE_UNIT_NONE:
                        snprintf(s, len, "%llu", (unsigned long long) pretty_value);
                        break;

                case SK_SMART_ATTRIBUTE_UNIT_UNKNOWN:
                        snprintf(s, len, "n/a");
                        break;

                case _SK_SMART_ATTRIBUTE_UNIT_MAX:
                        break;
        }

        s[len-1] = 0;

        return s;
}


int uppercase ( char *sPtr )
{
  while ( *sPtr != '\0' ) {
    *sPtr = toupper ( ( unsigned char ) *sPtr );
    ++sPtr;
  }
}


char* print_names(char *s, size_t len, uint8_t id, const char *k) {

        if (k)
                strncpy(s, k, len);
        else
                snprintf(s, len, "%u", id);

        
        s[len-1] = 0;
        uppercase(s);

        return s;
}