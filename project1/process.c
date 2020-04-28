#define _GNU_SOURCE
#include "process.h"
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#define GETTIME 334
#define PRINTK 335

extern Process *processes;

void proc_get_core(pid_t pid, int core_id)
{
	if (core_id > sizeof(cpu_set_t)) {
		fprintf(stderr, "Core index error.");
		exit(1);
	}

	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(core_id, &mask);
		
	if (sched_setaffinity(pid, sizeof(mask), &mask) < 0) {
		perror("sched_setaffinity");
		exit(1);
	}
}

void proc_create(int process_id)
{
	pid_t pid = fork();
    Process proc = processes[process_id];

	if (pid < 0) {
		perror("fork");
		exit(1);
	}

	if (pid == 0) {
		unsigned long start_sec, start_nsec, end_sec, end_nsec;
		char dmesg[256];
		syscall(GETTIME, &start_sec, &start_nsec);
		for (int i = 0; i < proc.t_exec; i++) {
			TIME_UNIT();
		}
		syscall(GETTIME, &end_sec, &end_nsec);
		sprintf(dmesg, "[project1] %d %lu.%09lu %lu.%09lu\n", getpid(), start_sec, start_nsec, end_sec, end_nsec);
		syscall(PRINTK, dmesg);
		exit(0);
	}
	
	/* Assign child to another core prevent from interupted by parant */
	proc_get_core(pid, CHILDCORE);
    processes[process_id].pid = pid;
}

void proc_block(pid_t pid)
{
	struct sched_param param;
	
	/* SCHED_IDLE should set priority to 0 */
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_IDLE, &param);
	
	if (ret < 0) {
		perror("sched_setscheduler block");
		exit(1);
	}
}

void proc_wakeup(pid_t pid)
{
	struct sched_param param;
	
	/* SCHED_OTHER should set priority to 0 */
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_OTHER, &param);
	
	if (ret < 0) {
		perror("sched_setscheduler wakeup");
		exit(1);
	}
}
