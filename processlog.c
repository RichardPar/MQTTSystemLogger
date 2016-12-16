
#include "globals.h"
#include "processlog.h"

int mqtt_ps_callback(char *node,char *msg, int len, void *p);


void start_processlog(void *pvt)
{
  char node[255];
    
  sprintf(node,"%s/LOG/PS",UID);
  mqtt_register_callback(node,&mqtt_ps_callback,pvt);
  sprintf(node,"ALL/LOG/PS");
  mqtt_register_callback(node,&mqtt_ps_callback,pvt);
}


int mqtt_ps_callback(char *node,char *msg, int len, void *p)
{
   	sg_process_stats *ps;
	size_t ps_size;
	size_t x;
	char *state = NULL;
    char outString[8192];
    char outNode[128];

    
   	ps = sg_get_process_stats(&ps_size);
	if(ps == NULL)
		return -1;

	qsort(ps, ps_size, sizeof *ps, sg_process_compare_pid);
    
    for(x=0;x<ps_size;x++){
		switch (ps->state) {
		case SG_PROCESS_STATE_RUNNING:
			state = "RUNNING";
			break;
		case SG_PROCESS_STATE_SLEEPING:
			state = "SLEEPING";
			break;
		case SG_PROCESS_STATE_STOPPED:
			state = "STOPPED";
			break;
		case SG_PROCESS_STATE_ZOMBIE:
			state = "ZOMBIE";
			break;
		case SG_PROCESS_STATE_UNKNOWN:
		default:
			state = "UNKNOWN";
			break;
		}
	sprintf(outString,"%u,%u,%u,%u,%u,%u,%u,%u,%u,%d,%f,%d,%s,%llu,%llu,%s,%s",
			(unsigned)ps->pid, (unsigned)ps->parent, (unsigned)ps->pgid,
			(unsigned)ps->uid, (unsigned)ps->euid, (unsigned)ps->gid, (unsigned)ps->egid,
			(unsigned)(ps->proc_size),
			(unsigned)(ps->proc_resident),
			(unsigned)ps->time_spent, (float)ps->cpu_percent,
			ps->nice, state,
			ps->voluntary_context_switches,
			ps->involuntary_context_switches,
			ps->process_name, ps->proctitle);
            
        sprintf(outNode,"LOG/PS");
        mqtt_writeresponse(outNode,outString,0);    
            
		ps++;
	}
  return 0;   
}