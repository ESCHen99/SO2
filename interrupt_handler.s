# 1 "interrupt_handler.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "interrupt_handler.S"
# 1 "include/asm.h" 1
# 2 "interrupt_handler.S" 2
# 1 "include/segment.h" 1
# 3 "interrupt_handler.S" 2
# 37 "interrupt_handler.S"
.globl keyboard_handler; .type keyboard_handler, @function; .align 0; keyboard_handler:
pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es
movb $0x20, %al; outb %al, $0x20;
call keyboard_routine
pop %ebx; pop %ecx; pop %edx; pop %esi; pop %edi; pop %ebp; pop %eax; pop %ds; pop %es; pop %fs; pop %gs;
iret

.globl syscall_handler; .type syscall_handler, @function; .align 0; syscall_handler:
    pushl %gs; pushl %fs; pushl %es; pushl %ds; pushl %eax; pushl %ebp; pushl %edi; pushl %esi; pushl %edx; pushl %ecx; pushl %ebx; movl $0x18, %edx; movl %edx, %ds; movl %edx, %es
    cmpl $0, %eax
    jl err
    cmpl $MAX_SYSCALL, %EAX
    jg err
    call *sys_call_table(, %eax, 0x04)
    jmp fin
err:
    movl $-38, %EAX
fin:
    movl %eax, 0x18(%esp)
    pop %ebx; pop %ecx; pop %edx; pop %esi; pop %edi; pop %ebp; pop %eax; pop %ds; pop %es; pop %fs; pop %gs;
    iret