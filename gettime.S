#include <asm.h>

ENTRY(gettime)
    push %ebp
    movl %esp, %ebp
    mov $0x0A, %eax
    int $0x80
    pop %ebp
    ret
    
