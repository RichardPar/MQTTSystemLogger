
#include <pthread.h>
#include <statgrab.h>

pthread_t vm_thread;
int vmlog_thread;
int vmlog_stop;

struct vmlog_t {
  int interval;
  pthread_t vm_thread;
  int vmlog_thread;
  int vmlog_stop;  
};

struct vmlog_t vmdata;

void start_vmlog(struct vmlog_t *p);

