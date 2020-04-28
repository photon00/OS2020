#include <sys/types.h>

typedef struct {
	char name[32];
	int t_ready;
	int t_exec;
	pid_t pid;
} Process;