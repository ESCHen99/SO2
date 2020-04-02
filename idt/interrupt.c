/*
 * interrupt.c -
 */
#include <types.h>
#include <interrupt.h>
#include <segment.h>
#include <hardware.h>
#include <io.h>
#include <devices.h>
#include <utils.h>
#include <errno.h>

#include <zeos_interrupt.h>


#define NUM_COLUMNS 80
#define NUM_ROWS    25



Gate idt[IDT_ENTRIES];
Register    idtR;

int zeos_ticks = 0;


char char_map[] =
{
  '\0','\0','1','2','3','4','5','6',
  '7','8','9','0','\'','¡','\0','\0',
  'q','w','e','r','t','y','u','i',
  'o','p','`','+','\0','\0','a','s',
  'd','f','g','h','j','k','l','ñ',
  '\0','º','\0','ç','z','x','c','v',
  'b','n','m',',','.','-','\0','*',
  '\0','\0','\0','\0','\0','\0','\0','\0',
  '\0','\0','\0','\0','\0','\0','\0','7',
  '8','9','-','4','5','6','+','1',
  '2','3','0','\0','\0','\0','<','\0',
  '\0','\0','\0','\0','\0','\0','\0','\0',
  '\0','\0'
};

void setInterruptHandler(int vector, void (*handler)(), int maxAccessibleFromPL)
{
  /***********************************************************************/
  /* THE INTERRUPTION GATE FLAGS:                          R1: pg. 5-11  */
  /* ***************************                                         */
  /* flags = x xx 0x110 000 ?????                                        */
  /*         |  |  |                                                     */
  /*         |  |   \ D = Size of gate: 1 = 32 bits; 0 = 16 bits         */
  /*         |   \ DPL = Num. higher PL from which it is accessible      */
  /*          \ P = Segment Present bit                                  */
  /***********************************************************************/
  Word flags = (Word)(maxAccessibleFromPL << 13);
  flags |= 0x8E00;    /* P = 1, D = 1, Type = 1110 (Interrupt Gate) */

  idt[vector].lowOffset       = lowWord((DWord)handler);
  idt[vector].segmentSelector = __KERNEL_CS;
  idt[vector].flags           = flags;
  idt[vector].highOffset      = highWord((DWord)handler);
}

void setTrapHandler(int vector, void (*handler)(), int maxAccessibleFromPL)
{
  /***********************************************************************/
  /* THE TRAP GATE FLAGS:                                  R1: pg. 5-11  */
  /* ********************                                                */
  /* flags = x xx 0x111 000 ?????                                        */
  /*         |  |  |                                                     */
  /*         |  |   \ D = Size of gate: 1 = 32 bits; 0 = 16 bits         */
  /*         |   \ DPL = Num. higher PL from which it is accessible      */
  /*          \ P = Segment Present bit                                  */
  /***********************************************************************/
  Word flags = (Word)(maxAccessibleFromPL << 13);

  //flags |= 0x8F00;    /* P = 1, D = 1, Type = 1111 (Trap Gate) */
  /* Changed to 0x8e00 to convert it to an 'interrupt gate' and so
     the system calls will be thread-safe. */
  flags |= 0x8E00;    /* P = 1, D = 1, Type = 1110 (Interrupt Gate) */

  idt[vector].lowOffset       = lowWord((DWord)handler);
  idt[vector].segmentSelector = __KERNEL_CS;
  idt[vector].flags           = flags;
  idt[vector].highOffset      = highWord((DWord)handler);
}



void keyboard_routine(){
    if(inb(0x60) & 0x80){
        char aux = char_map[inb(0x60) & 0x7F];
        if(aux == 0) aux = 'C';
        printc_color(aux, white);
        if(aux == '0') task_switch(idle_task);
        if(aux == '1') task_switch(task1_task);
        if(aux == 'f') task_switch(list_entry(list_first(&readyqueue), struct task_struct, list));
        if(aux == 's'){
          //Testing the scheduler
          schedule(); 
        }
    }
}

#define sys_writeBUFF 256

int sys_write(int fd, char* buffer, int size){
    if(fd != 1) return -81;        // EBDFD
    if(buffer == NULL) return -14; // ENULLPTR
    if(size < 0) return -5;        // ENEGSIZE

    char sys_buffer[sys_writeBUFF];
    while(size > sys_writeBUFF){
        if(copy_from_user(buffer, sys_buffer, sys_writeBUFF) >= 0)
            sys_write_console(sys_buffer, sys_writeBUFF);
        else return -1;
        size -= sys_writeBUFF;
    }
    if(copy_from_user(buffer, sys_buffer, size) >= 0)
        sys_write_console(sys_buffer, size);
    else return -1;                 // EUNSPECIFIED
    return 0;
}

void printkn(int n){
    if(n < 10){
      printc_color('0' + n, white);
    }
    else{
      printkn(n/10);
      printkn((n)%10);
    }        
}

void debug(int n){
  printk("Debug called from function: ");
  printkn(n);
  printk('\n');
}

int sys_get_stats(int pid, struct stats *st){
//       printk("Hello from sys_get_stats\n");
//       printkn(pid);
       if(pid < 0) return -EINVALSKIPPED;
       if(!access_ok(VERIFY_WRITE, st, sizeof(*st))) return -6;//-EFAULTSKIPPED;
       init_stat(st);
       for(int i = 0; i < NR_TASKS; ++i){
         if(task[i].task.PID == pid){
            struct stats aux = task[i].task.stat;
            st->user_ticks = aux.user_ticks;
            st->system_ticks = aux.system_ticks;
            st->blocked_ticks = aux.blocked_ticks;
            st->ready_ticks = aux.ready_ticks;
            st->elapsed_total_ticks = aux.elapsed_total_ticks;
            st -> total_trans = aux.total_trans;
            st -> remaining_ticks = aux.remaining_ticks;
            return 0;
         }       
       }
       return -ESRCHSKIPPED;
}
int sys_gettime(){
   return zeos_ticks; 
}

void clock_routine(){
    ++zeos_ticks;
    zeos_show_clock();
    schedule();
}



void setIdt()
{
  /* Program interrups/exception service routines */
  idtR.base  = (DWord)idt;
  idtR.limit = IDT_ENTRIES * sizeof(Gate) - 1;

  set_handlers();
  setInterruptHandler(33, keyboard_handler, 0);
  setInterruptHandler(32, clock_handler, 0);
  setTrapHandler(0x80, syscall_handler, 3);
  /* ADD INITIALIZATION CODE FOR INTERRUPT VECTOR */
  set_idt_reg(&idtR);
  writeMSR(0x174, __KERNEL_CS);
  writeMSR(0x175, INITIAL_ESP);
  writeMSR(0x176, (int) syscall_handler_sysenter);

}

