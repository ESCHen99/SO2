#include <asm.h>

ENTRY(fast_write)
	push %ebp               // Save caller %ebp
	mov %esp, %ebp          
	push %ebx               // Save caller %ebx

	mov $0x04, %eax         // syscall number
	mov  8(%ebp), %ebx      // syscall arguments
	mov 12(%ebp), %ecx
	mov 16(%ebp), %edx
	
	push %ecx               // Save sysexit registers
	push %edx

	push $return_syscall    // push syscall return address

	push %ebp               // push user stack
    mov %esp, %ebp		    // syscall stack
    	
	sysenter

return_syscall:
    cmpl $0, %eax           // result management
    jge fin
    negl %eax
	movl %eax, errno        // Update errno with error code
    movl $-1, %eax          // return -1; to the caller
fin:
    popl %ebp               // Restore caller state
    add $4, %esp
	pop %edx
	pop %ecx
	pop %ebx
    movl %ebp, %esp
	pop %ebp
	ret
