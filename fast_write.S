#include <asm.h>

ENTRY(fast_write)
	push %ebp
	mov %esp, %ebp
	push %ebx
	mov $0x04, %eax
	mov  8(%ebp), %ebx
	mov 12(%ebp), %ecx
	mov 16(%ebp), %edx
	
	push %ecx
	push %edx
	push $return_syscall
	push %ebp
	mov  %esp, %ebx
		
	
	sysenter
return_syscall:
	pop %ebp
	add $4, %esp
	pop %edx
	pop %ecx
	pop %ebx
	pop %ebp
	ret
