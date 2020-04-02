/*
 * sched.c - initializes struct for task 0 anda task 1
 */

#include <sched.h>
#include <mm.h>
#include <io.h>
#include <list.h>
#include <errno.h>
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


void init_stat(struct stats* st){
  st->user_ticks = 0;
  st->system_ticks = 0;
  st->blocked_ticks = 0;
  st->ready_ticks = 0;
  st->elapsed_total_ticks = 0;
  st -> total_trans = 0;
  st -> remaining_ticks = 0;
}

void init_task_system(){
  PID_counter = 0;
	INIT_LIST_HEAD(&readyqueue);	
	INIT_LIST_HEAD(&freequeue);
	for(int i = 0; i < NR_TASKS; ++i){
		list_add_tail(&(task[i].task.list), &freequeue);
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
      int aux = sys_gettime();
      while(sys_gettime() - aux < 200);
      printk("idle\n");
	;
	}
}

struct task_struct* list_head_to_task_struct(struct list_head* l){
  return list_entry(l, struct task_struct, list);
}

void init_idle (void)
{
	struct list_head* task = list_first(&freequeue); // Fetch the first free task to be idle
 	struct task_struct* real_task = list_entry(task, struct task_struct, list);
	list_del(task);
	real_task -> PID = 0;                            // Process PID = 0
  real_task -> quantum = DEFAULT_QUANTUM;
	allocate_DIR(real_task);                         // Allocate directory table

  union task_union* real_kernel_stack = real_task; // kernel_stack (task_union) pointer
  
  real_kernel_stack -> stack[KERNEL_STACK_SIZE - 1] = &cpu_idle; // Base of stack @of function to be executed
  real_kernel_stack -> stack[KERNEL_STACK_SIZE - 2] = 0xfe00fe00; // random %ebp for debug purposes
  real_task -> kernel_esp = &(real_kernel_stack->stack[KERNEL_STACK_SIZE-2]); // Update kernel_sack for task_switch
                                                                                // %ebp
	//task_switch(real_task);
	idle_task = real_task;
  ++PID_counter;
}

int get_fork_ebp();

void init_task1(void)
{
   struct list_head* task = list_first(&freequeue);
   struct task_struct* real_task = list_entry(task, struct task_struct, list);
   list_del(task);
   real_task -> PID = 0x1;
   real_task -> quantum = DEFAULT_QUANTUM;
   allocate_DIR(real_task);

   set_user_pages(real_task); 
   tss.esp0 = (int)real_task + (int) (KERNEL_STACK_SIZE)*sizeof(long); //Assuming task_switch structure??? 
   writeMSR(0x175, tss.esp0);

   //tss.esp0 = real_task;
   set_cr3(real_task -> dir_pages_baseAddr);
   task1_task = real_task;
   init_stat(&(real_task->stat));
   ++PID_counter;
}

int inner_task_switch(union task_union* new, int current_ebp){
  tss.esp0 = ((int) new + (int) KERNEL_STACK_SIZE*sizeof(long)); 
  struct task_struct* real_task = current();
  
  real_task -> kernel_esp = current_ebp; // %ebx %edi %esi 

  set_cr3(new -> task.dir_pages_baseAddr);
  return (new -> task.kernel_esp );
}



void init_sched()
{
 current_quantum = DEFAULT_QUANTUM;
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


int get_quantum(struct task_struct *t){
  return t->quantum;        
}

void set_quantum(struct task_struct *t, int new_quantum){
  t->quantum = new_quantum;        
}

void sched_next_rr(){
  struct task_struct* next_task = idle_task;
  if(!list_empty(&readyqueue)){
    struct list_head* task = list_first(&readyqueue);
    next_task = list_entry(task, struct task_struct, list);
    update_process_state_rr(next_task, NULL); 

    ++next_task->stat.total_trans;
  }
  current_quantum = get_quantum(next_task);
  next_task->stat.remaining_ticks = current_quantum;

  next_task->stat.ready_ticks += get_ticks() - next_task ->stat.elapsed_total_ticks;
  next_task->stat.elapsed_total_ticks = get_ticks(); // d)
  
  
  task_switch(next_task);
}

void update_process_state_rr(struct task_struct *t, struct list_head *dest){
  if(t->list.next != NULL & t->list.next != NULL) list_del(&(t->list));
  if(dest != NULL){
          list_add_tail(&(t->list), dest);
  }
}

int needs_sched_rr(){
  return current_quantum == 0;        
}

void update_sched_data_rr(){
   --current_quantum;
   current()->stat.remaining_ticks = current_quantum;
}

void schedule(){
  update_sched_data_rr();
  if(needs_sched_rr()){
    struct task_struct* current_task = current();
    if(current_task != idle_task) update_process_state_rr(current_task, &readyqueue);

    if(list_empty(&readyqueue)){
      task_switch(idle_task);        
    }
    else{
      current_task->stat.system_ticks += get_ticks() - current_task -> stat.elapsed_total_ticks; // c)
      current_task->stat.elapsed_total_ticks = get_ticks();
      sched_next_rr();
    }
  }
}

void user_to_system(){
  current()->stat.user_ticks += get_ticks() - current()->stat.elapsed_total_ticks;
  current()->stat.elapsed_total_ticks = get_ticks();
}

void system_to_user(){
  current()->stat.system_ticks += get_ticks() - current()->stat.elapsed_total_ticks;
  current()->stat.elapsed_total_ticks = get_ticks();       
}
