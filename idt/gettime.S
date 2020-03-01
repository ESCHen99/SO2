#include <asm.h>

ENTRY(gettime)
    push %ebp
    movl %esp, %ebp
    mov $0x0A, %eax
    int $0x80
    pop %ebp
    ret

ENTRY(fast_gettime)
    push %ebp
    movl %esp, %ebp
    movl $0x0A, %eax
    push $return_syscall
    push %ebp
    movl %esp, %ebp
    sysenter
return_syscall:
    pop  %ebp
    add  $4, %esp
    pop  %ebp
    ret
