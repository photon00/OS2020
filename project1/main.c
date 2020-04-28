#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "process.h"

#define FIFO 0
#define RR   1
#define SJF  2
#define PSJF 3
#define TIME_QUANTUM 500

/* global variables */
Process *processes;
int policy, nproc, running;
int *RR_queue, head, tail, qlen;
int current_time, last_switch;

int compare(const void *a, const void *b) {  // sort by ready time
    return  ((Process*)a)->t_ready - ((Process*)b)->t_ready;
}
void emulation();
int scheduling();
void enqueue(int i){  RR_queue[tail] = i; tail = (tail+1)%nproc; qlen++; }
void dequeue(){ head = (head+1)%nproc; qlen--; }
#ifdef DEBUG
void show_queue(){
	fprintf(stderr, "RR_queue: ");
	for (int i=0; i<qlen; i++)
		fprintf(stderr, "%d ", RR_queue[(head+i)%nproc]);
	fprintf(stderr, "\n");
}	
#endif


int main(){
    char sched_policy[256];
    scanf("%s", sched_policy);
    scanf("%d", &nproc);

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

    processes = malloc(nproc * sizeof(Process));
	RR_queue = malloc((nproc+1) * sizeof(int));

    for (int i=0; i<nproc; ++i){
        scanf("%s%d%d", processes[i].name, &processes[i].t_ready, &processes[i].t_exec);
		processes[i].pid = -1;
    }
    
	emulation();
    free(processes);
	free(RR_queue);
    exit(0);
}

void emulation(){
	int nfinish = 0;

	qsort((void*)processes, nproc, sizeof(Process), compare);  // sort process by ready time
	proc_get_core(getpid(), PARENTCORE);
	proc_wakeup(getpid());
    
	running = -1;  // no process is running at begining
    while (1){
		/* create process when it's ready */
		for (int i=0; i<nproc; ++i){
			if (processes[i].t_ready == current_time){
				proc_create(i);
				proc_block(processes[i].pid);
#ifdef DEBUG
			fprintf(stderr, "%s ready at time %d.\n", processes[i].name, current_time);
#endif
				if (policy == RR){
					enqueue(i);
#ifdef DEBUG
					show_queue();
#endif
				}
			}	
		}

		/* dispose finish process */
		if (running != -1 && processes[running].t_exec == 0){
			waitpid(processes[running].pid, NULL, 0);
#ifdef DEBUG
			fprintf(stderr, "%s finish at time %d.\n", processes[running].name, current_time);
#endif
			printf("%s %d\n", processes[running].name, processes[running].pid);
			running = -1;
			nfinish++;
			if (policy == RR){
				dequeue();
#ifdef DEBUG
				show_queue();
#endif
			}
			if (nfinish == nproc) break;  // all process finish
		}

		/* perform schedule */
		int next_proc = scheduling();
		if (running != next_proc){  // perform context switch
#ifdef DEBUG
			fprintf(stderr, "context switch at time %d (%d -> %d).\n",current_time, 
				running, next_proc);
			if (policy == RR) show_queue();
#endif
			if (next_proc != -1)
				proc_wakeup(processes[next_proc].pid);
			if (running != -1)
				proc_block(processes[running].pid);
			running = next_proc;
			last_switch = current_time;
		}

		TIME_UNIT();
		if (running != -1)
			processes[running].t_exec--;
		current_time++;
	}
}

int scheduling(){
	/* non-preemptive */
	if (running != -1 && (policy == SJF || policy == FIFO))
		return running;

	int ret = -1;
	if (policy == PSJF || policy ==  SJF) {
		for (int i = 0; i < nproc; i++) {
			if (processes[i].pid == -1 || processes[i].t_exec == 0)
				continue;
			if (ret == -1 || processes[i].t_exec < processes[ret].t_exec)
				ret = i;
		}
	}
	
	else if (policy == FIFO){
		for(int i = 0; i < nproc; i++) {
			if(processes[i].t_exec > 0 && processes[i].pid != -1){
				ret = i;
				break;
			}
		}
	}

	else if (policy == RR){
		/* re-queueing unfinished process */
		if (running != -1 && ((current_time-last_switch) % 500 == 0)){
			enqueue(RR_queue[head]);
			dequeue();
		}
		/* choose fist element in queue if not empty */
		if (qlen > 0)
			ret = RR_queue[head];
	}
	return ret;
}