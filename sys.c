/*
 * sys.c - Syscalls implementation
 */
#include <devices.h>

#include <utils.h>

#include <io.h>

#include <mm.h>

#include <mm_address.h>

#include <sched.h>

#include <errno.h>

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


int ret_from_fork(){
  return 0;        
}

void free_task_struct(struct task_struct* current){
  free_user_pages(current);
  current->PID = 0xfefefefe;
}

int sys_exit(){
  update_process_state_rr(current(), &freequeue);
  
  free_task_struct(current());
  sched_next_rr(); 
  return 0;
}

int sys_fork(void){
  if(list_empty(&freequeue)) return -ENOMEM; // Too many process already
  struct list_head* task = list_first(&freequeue); // a) get a free task_struct     
  list_del(task);
  struct task_struct* child_task = list_entry(task, struct task_struct, list);
  struct task_struct* parent_task = current();
  
  copy_data(parent_task, child_task, sizeof(union task_union)); // b)
  // I need to modify parent page table in order to modify child data otherwise no there is no way toaccess child physical data


  allocate_DIR(child_task); // c)
  share_code_pages(parent_task, child_task); // Share parent and child code addr. space.
  if(new_data_pages(child_task) < 0) return -ENOMEM; // Child_process data has its own addr. space.

  
  page_table_entry* child_PT = get_PT(child_task);
  for(int pag = 0; pag < NUM_PAG_DATA; ++pag){
    int aux_frame = child_PT[PAG_LOG_INIT_DATA+pag].bits.pbase_addr; // Child DATA + STACK frame
    set_ss_pag(get_PT(parent_task), PAG_LOG_INIT_DATA + NUM_PAG_DATA + pag, aux_frame); // Redirecte Empty parent frame to Child DATA + STACK frame
  }


  copy_data((void *) ((int) PAG_LOG_INIT_DATA<<12), (void *) ((int) (PAG_LOG_INIT_DATA + NUM_PAG_DATA)<<12), NUM_PAG_DATA*4096); // Copy parent DATA + STACK to child.

  for(int pag = 0; pag < NUM_PAG_DATA; ++pag){
    del_ss_pag(get_PT(parent_task), PAG_LOG_INIT_DATA + NUM_PAG_DATA + pag); // Unlink parent.    
  }

  set_cr3(parent_task->dir_pages_baseAddr); // Flush TLB;
  child_task -> PID = PID_counter++; // New PID for child
  child_task -> quantum = parent_task -> quantum;
  // Update kernel_esp:
  child_task -> kernel_esp = (int) child_task + (int)get_fork_ebp()%4096 - 4;
  int* child_stack_ebp = (int*) child_task -> kernel_esp;
  child_stack_ebp[0] = 0xfcfcfcfc;
  child_stack_ebp[1] = (int) ret_from_fork;
  
  list_add_tail(task, &readyqueue);
  init_stat(&(child_task->stat));
  return child_task -> PID;

}

/**
int sys_fork()
{
  int PID=-1;

  // creates the child process
  
  return PID;
}


void sys_exit()
{  
}*/

