/*
 * interrupt.h - Definició de les diferents rutines de tractament d'exepcions
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <types.h>

#define IDT_ENTRIES 256

extern Gate idt[IDT_ENTRIES];
extern Register idtR;

void setInterruptHandler(int vector, void (*handler)(), int maxAccessibleFromPL);
void setTrapHandler(int vector, void (*handler)(), int maxAccessibleFromPL);

void setIdt();


/* Hardware interrupt handler*/

void keyboard_handler();
void keyboard_routine();

void clock_handler();
void clock_routine();

/* syscall handler*/

// sysentry mode
void writeMSR(int addr, int value);

void syscall_handler_sysenter();

// int mode
void syscall_handler();

int sys_write(int fd, char* buffer, int size);
int sys_gettime();


#endif  /* __INTERRUPT_H__ */
