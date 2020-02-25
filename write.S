#include <asm.h>

ENTRY(write)
    push %esp
    mov %esp, %ebp
    
    mov  8(%ebp), %ebx
    mov 12(%ebp), %ecx
    mov 16(%ebp), %edx
    mov $0x04, %eax
    int $0x80

    popl %ebp
    ret
