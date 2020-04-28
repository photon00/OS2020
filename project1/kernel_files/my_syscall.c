#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>

// syscall(334, long*, long*)
asmlinkage void sys_my_gettime(long *sec, long *nsec)
{
    struct timespec ts;
    getnstimeofday(&ts);
    *sec = ts.tv_sec;
    *nsec = ts.tv_nsec;
}
// syscall(335, char*)
asmlinkage void sys_my_printk(char msg[])
{
    printk(msg);
}