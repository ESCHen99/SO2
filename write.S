#include <asm.h>

ENTRY(write)
    push %ebp               // Save caller %ebp
    mov %esp, %ebp
   	push %ebx               // Save %ebx
 
    mov  8(%ebp), %ebx      // syscall arguments
    mov 12(%ebp), %ecx
    mov 16(%ebp), %edx
    mov $0x04, %eax         // syscall number
    int $0x80
    cmpl  $0, %eax	        // Return negative value
    jge fin
    negl %eax
    mov %eax, errno         // Update errno with error code
    mov $-1, %eax           // return -1; if error
fin:
    pop %ebx                // Restore caller %ebp
    movl %ebp, %esp
    popl %ebp               // Restore caller %ebx
    ret
