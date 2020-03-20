# 1 "idt/write.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "idt/write.S"
# 1 "include/asm.h" 1
# 2 "idt/write.S" 2

.globl write; .type write, @function; .align 0; write:
    push %ebp
    mov %esp, %ebp
    push %ebx

    mov 8(%ebp), %ebx
    mov 12(%ebp), %ecx
    mov 16(%ebp), %edx
    mov $0x04, %eax
    int $0x80
    cmpl $0, %eax
    jge fin
    negl %eax
    mov %eax, errno
    mov $-1, %eax
fin:
    pop %ebx
    movl %ebp, %esp
    popl %ebp
    ret
