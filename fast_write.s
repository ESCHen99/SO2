# 1 "fast_write.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "fast_write.S"
# 1 "include/asm.h" 1
# 2 "fast_write.S" 2

.globl fast_write; .type fast_write, @function; .align 0; fast_write:
 push %ebp
 mov %esp, %ebp
 push %ebx
 mov $0x04, %eax
 mov 8(%ebp), %ebx
 mov 12(%ebp), %ecx
 mov 16(%ebp), %edx

 push %ecx
 push %edx
 push $return_syscall
 push %ebp
 mov %esp, %ebx


 sysenter
return_syscall:
 pop %ebp
 add $4, %esp
 pop %edx
 pop %ecx
 pop %ebx
 pop %ebp
 ret
