# 1 "write.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "write.S"
# 1 "include/asm.h" 1
# 2 "write.S" 2

.globl write; .type write, @function; .align 0; write:
    push %esp
    mov %esp, %ebp

    mov 8(%ebp), %ebx
    mov 12(%ebp), %ecx
    mov 16(%ebp), %edx
    mov $0x04, %eax
    int $0x80

    popl %ebp
    ret