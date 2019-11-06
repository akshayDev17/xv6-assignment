#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"
#include<stddef.h>

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// new waitx syscall
int
sys_waitx( void ){

  int *rtime, *wtime;
  if(argptr(0, (char**)&wtime, sizeof(int)) < 0)
    return 12;

  if(argptr(1, (char**)&rtime, sizeof(int)) < 0)
    return 13;

  return waitx(wtime,rtime);
}

// new ps syscall
int 
sys_ps( void ){
  return ps();
}

// new getpinfo syscall
int 
sys_getpinfo( void ){
  return getpinfo();
}

// change priority of a process
int
sys_chpr(void)
{
    int pid, pr;
    if(argint(0, &pid) < 0)
        return -1;
    if(argint(1, &pr) < 0)
        return -1;

    return chpr(pid, pr);
}

// yield syscall

int sys_yield(void) {
  yield();
  return 0;
}