# 1 "idt/gettime.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "idt/gettime.S"
# 1 "include/asm.h" 1
# 2 "idt/gettime.S" 2

.globl gettime; .type gettime, @function; .align 0; gettime:
    push %ebp
    movl %esp, %ebp
    mov $0x0A, %eax
    int $0x80
    pop %ebp
    ret

.globl fast_gettime; .type fast_gettime, @function; .align 0; fast_gettime:
    push %ebp
    movl %esp, %ebp
    movl $0x0A, %eax
    push $return_syscall
    push %ebp
    movl %esp, %ebp
    sysenter
return_syscall:
    pop %ebp
    add $4, %esp
    pop %ebp
    ret
