# 1 "idt/writeMSR.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "idt/writeMSR.S"
# 1 "include/asm.h" 1
# 2 "idt/writeMSR.S" 2

.globl writeMSR; .type writeMSR, @function; .align 0; writeMSR:
 push %ebp
 mov %esp, %ebp

 mov 8(%esp), %ecx
 mov 12(%esp), %eax

 wrmsr
 pop %ebp
 ret
