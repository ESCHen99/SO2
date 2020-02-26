# 1 "gettime.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "gettime.S"
# 1 "include/asm.h" 1
# 2 "gettime.S" 2

.globl gettime; .type gettime, @function; .align 0; gettime:
    push %ebp
    movl %esp, %ebp
    mov $0x0A, %eax
    int $0x80
    pop %ebp
    ret
