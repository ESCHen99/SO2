#include <asm.h>

ENTRY(write)
    push %esp
    mov %esp, %ebp
   	push %ebx
 
    mov  8(%ebp), %ebx
    mov 12(%ebp), %ecx
    mov 16(%ebp), %edx
    mov $0x04, %eax
    int $0x80
	
	pop %ebx
    popl %ebp
    ret
