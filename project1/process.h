#include <sys/types.h>

#define TIME_UNIT() { volatile unsigned long i; for(i=0;i<1000000UL;i++); }
#define PARENTCORE 0
#define CHILDCORE  1

typedef struct {
	char name[32];
	int t_ready;
	int t_exec;
	pid_t pid;
} Process;

void proc_get_core(pid_t pid, int core_id);
void proc_create(int id);
void proc_wakeup(pid_t pid);
void proc_block(pid_t pid);