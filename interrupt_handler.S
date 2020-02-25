#include <asm.h>
#include <segment.h>

#define SAVE_ALL \
      pushl %gs; \
      pushl %fs; \
      pushl %es; \
      pushl %ds; \
      pushl %eax; \
      pushl %ebp; \
      pushl %edi; \
      pushl %esi; \
      pushl %edx; \
      pushl %ecx; \
      pushl %ebx; \
      movl $__KERNEL_DS, %edx;    \
      movl %edx, %ds;           \
      movl %edx, %es

#define RESTORE_ALL \
      pop %ebx; \
      pop %ecx; \
      pop %edx; \
      pop %esi; \
      pop %edi; \
      pop %ebp; \
      pop %eax; \
      pop %ds; \
      pop %es; \
      pop %fs; \
      pop %gs; \

#define EOI \
    movb $0x20, %al; \
    outb %al, $0x20; \

ENTRY(keyboard_handler)
SAVE_ALL
EOI
call keyboard_routine
RESTORE_ALL
iret

ENTRY(clock_handler)
SAVE_ALL
EOI
call clock_routine
RESTORE_ALL
iret

ENTRY(syscall_handler)
    SAVE_ALL
    cmpl $0, %eax
    jl err
    cmpl $MAX_SYSCALL, %EAX
    jg err
    call *sys_call_table(, %eax, 0x04)
    jmp fin
err:
    movl $-38, %EAX
fin:
    movl %eax, 0x18(%esp)
    RESTORE_ALL
    iret    