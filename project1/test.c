#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>

int main(){
    char msg[256];
    long sec, nsec;
    syscall(334, &sec, &nsec);
    sprintf(msg, "TEST TEST TEST %lu.%lu\n", sec, nsec);
    syscall(335, msg);
    
    syscall(334, &sec, &nsec);
    sprintf(msg, "TEST TEST TEST %lu.%lu\n", sec, nsec);
    syscall(335, msg);
    exit(0);
}