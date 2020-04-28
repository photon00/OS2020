#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"

#define FIFO 0
#define RR   1
#define SJF  2
#define PSJF 3

int compare(const void *a, const void *b) {  // sort by ready time
    return  ((Process*)a)->t_ready - ((Process*)b)->t_ready;
}
void scheduling();


/* global variables */
Process *processes;
int policy, nproc;

int main(){
    char sched_policy[256];
    scanf("%s", sched_policy);
    scanf("%d", &nproc);

    processes = malloc(nproc * sizeof(Process));
    for (int i=0; i<nproc; ++i){
        scanf("%s%d%d", processes[i].name, &processes[i].t_ready, &processes[i].t_exec);
    }
    
    if (strcmp(sched_policy, "FIFO") == 0) {
		policy = FIFO;
	}
	else if (strcmp(sched_policy, "RR") == 0) {
		policy = RR;
	}
	else if (strcmp(sched_policy, "SJF") == 0) {
		policy = SJF;
	}
	else if (strcmp(sched_policy, "PSJF") == 0) {
		policy = PSJF;
	}
	else {
		fprintf(stderr, "Invalid policy: %s", sched_policy);
		exit(1);
	}

    scheduling();
    free(processes);
    exit(0);
}

void scheduling(){
    qsort((void*)processes, nproc, sizeof(Process), compare);
    
}