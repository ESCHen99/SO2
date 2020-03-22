/*
 * sched.c - initializes struct for task 0 anda task 1
 */

#include <sched.h>
#include <mm.h>
#include <io.h>
#include <list.h>

/* Declate and initialize a freequeue*/

//struct list_head 

union task_union task[NR_TASKS]
  __attribute__((__section__(".data.task")));

#if 0
struct task_struct *list_head_to_task_struct(struct list_head *l)
{
  return list_entry( l, struct task_struct, list);
}
#endif



extern struct list_head blocked;


void init_task_system(){
	INIT_LIST_HEAD(&readyqueue);	
	INIT_LIST_HEAD(&freequeue);
	for(int i = 0; i < NR_TASKS; ++i){
		list_add(&(task[i].task.list), &freequeue);
	}
}

/* get_DIR - Returns the Page Directory address for task 't' */
page_table_entry * get_DIR (struct task_struct *t) 
{
	return t->dir_pages_baseAddr;
}

/* get_PT - Returns the Page Table address for task 't' */
page_table_entry * get_PT (struct task_struct *t) 
{
	return (page_table_entry *)(((unsigned int)(t->dir_pages_baseAddr->bits.pbase_addr))<<12);
}


int allocate_DIR(struct task_struct *t) 
{
	int pos;

	pos = ((int)t-(int)task)/sizeof(union task_union);

	t->dir_pages_baseAddr = (page_table_entry*) &dir_pages[pos]; 

	return 1;
}

void cpu_idle(void)
{
	__asm__ __volatile__("sti": : :"memory");

	while(1)
	{
	;
	}
}

void init_idle (void)
{
	struct list_head* task = list_first(&freequeue); // Fetch the first free task to be idle
 	struct task_struct* real_task = list_entry(task, struct task_struct, list);
	real_task -> PID = 0;                            // Process PID = 0
	allocate_DIR(real_task);                         // Allocate directory table

  union task_union* real_kernel_stack = real_task; // kernel_stack (task_union) pointer
  
  real_kernel_stack -> stack[KERNEL_STACK_SIZE - 1] = &cpu_idle; // Base of stack @of function to be executed
  real_kernel_stack -> stack[KERNEL_STACK_SIZE - 2] = 0xfe00fe00; // random %ebp for debug purposes
  real_task -> kernel_esp = &(real_kernel_stack->stack[KERNEL_STACK_SIZE-2]); // Update kernel_sack for task_switch
                                                                                // %ebp
	//task_switch(real_task);
	idle_task = real_task;
	list_del(task);
}

void init_task1(void)
{
   struct list_head* task = list_first(&freequeue);
   struct task_struct* real_task = list_entry(task, struct task_struct, list);
   real_task -> PID = 0xfefefefe;
   allocate_DIR(real_task);

   set_user_pages(real_task); 
   tss.esp0 = 0x1cfff; //real_task + (KERNEL_STACK_SIZE)*sizeof(long) - 1; //Assuming task_switch structure??? 
   //tss.esp0 = real_task;
   set_cr3(real_task -> dir_pages_baseAddr);
   list_del(task);
}

int inner_task_switch(union task_union* new){
  tss.esp0 = (new -> task.kernel_esp);    
  struct task_struct* real_task = current();
  real_task -> kernel_esp = get_current_ebp(); 
   
  set_cr3(new -> task.dir_pages_baseAddr);
  return new -> task.kernel_esp;
}

void init_sched()
{

}

struct task_struct* current()
{
  int ret_value;
  
  __asm__ __volatile__(
  	"movl %%esp, %0"
	: "=g" (ret_value)
  );
  return (struct task_struct*)(ret_value&0xfffff000);
}

