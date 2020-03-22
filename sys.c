/*
 * sys.c - Syscalls implementation
 */
#include <devices.h>

#include <utils.h>

#include <io.h>

#include <mm.h>

#include <mm_address.h>

#include <sched.h>

#define LECTURA 0
#define ESCRIPTURA 1

int check_fd(int fd, int permissions)
{
  if (fd!=1) return -9; /*EBADF*/
  if (permissions!=ESCRIPTURA) return -13; /*EACCES*/
  return 0;
}

int sys_ni_syscall()
{
	return -38; /*ENOSYS*/
}

int sys_getpid()
{
	return current()->PID;
}

int sys_fork(void){
  int PID = -1;
  if(list_empty(&freequeue)) return PID; // Too many process already
  struct list_head* task = list_first(&freequeue); // a) get a free task_struct     
  struct task_struct* child_task = list_entry(task, struct task_struct, list);
  struct task_struct* parent_task = current();
  copy_data(parent_task, child_task, sizeof(union task_union)); // b)
  // I need to modify parent page table in order to modify child data otherwise no there is no way toaccess child physical data


  allocate_DIR(child_task); // c)
}

/**
int sys_fork()
{
  int PID=-1;

  // creates the child process
  
  return PID;
}*/

void sys_exit()
{  
}
