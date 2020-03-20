#include <asm.h>

ENTRY(current)
push %ebp
mov %esp, %ebp

mov %esp, %eax
and $0xFFFFF000, %eax

pop %ebp
ret 
