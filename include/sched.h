
/*
 * sched.h - Estructures i macros pel tractament de processos
 */

#ifndef __SCHED_H__
#define __SCHED_H__

#include <list.h>
#include <types.h>
#include <stats.h>
#include <mm_address.h>

#define NR_TASKS      10
#define KERNEL_STACK_SIZE	1024

#define DEFAULT_QUANTUM 20
#define RUNNING 0
#define READY 1
#define BLOCKED 2

enum state_t { ST_RUN, ST_READY, ST_BLOCKED };

struct list_head freequeue;

struct list_head readyqueue;



struct task_struct {
  int PID;			/* Process ID. This MUST be the first field of the struct. */
  page_table_entry * dir_pages_baseAddr;
  int kernel_esp;
  struct list_head list;
  int quantum;
  struct stats stat;
};

void schedule();

union task_union {
  struct task_struct task;
  unsigned long stack[KERNEL_STACK_SIZE];    /* pila de sistema, per procés */
};

extern union task_union task[NR_TASKS]; /* Vector de tasques */


#define KERNEL_ESP(t)       	(DWord) &(t)->stack[KERNEL_STACK_SIZE]

#define INITIAL_ESP       	KERNEL_ESP(&task[1])

/* Init freequeue*/

int PID_counter;

void init_stat(struct stats* st);

void init_task_system();

/* Inicialitza les dades del proces inicial */
struct task_struct* task1_task;

struct task_struct* list_head_to_task_struct(struct list_head* l);

void init_task1(void);

struct task_struct* idle_task;

void init_idle(void);

void init_sched(void);

struct task_struct * current();

int get_current_ebp();

void load_esp(unsigned int new_ebp);

int inner_task_switch(union task_union* t, int current_ebp);

void task_switch(union task_union*t);



struct task_struct *list_head_to_task_struct(struct list_head *l);

int allocate_DIR(struct task_struct *t);

page_table_entry * get_PT (struct task_struct *t) ;

page_table_entry * get_DIR (struct task_struct *t) ;

/* Headers for the scheduling policy */
int current_quantum;

void sched_next_rr();
void update_process_state_rr(struct task_struct* t, struct list_head* dest);
int needs_sched_rr();
void update_sched_data_rr();

int get_quantum(struct task_struct* t);
void set_quantum(struct task_struct* t, int new_quantum);

#endif  /* __SCHED_H__ */
