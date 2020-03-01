#include <asm.h>

ENTRY(writeMSR)
	push %ebp
	mov %esp, %ebp
	
	mov 8(%esp), %ecx
	mov 12(%esp), %eax
	
	wrmsr  
	pop %ebp
	ret
