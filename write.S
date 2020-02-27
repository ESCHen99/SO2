#include <asm.h>

ENTRY(write)
    push %ebp
    mov %esp, %ebp
   	push %ebx
 
    mov  8(%ebp), %ebx
    mov 12(%ebp), %ecx
    mov 16(%ebp), %edx
    mov $0x04, %eax
    int $0x80
    cmpl  $0, %eax	// Return negative value
    jge fin
    negl %eax
    mov %eax, errno
    mov $-1, %eax
fin:
    pop %ebx
    movl %ebp, %esp
    popl %ebp
    ret
