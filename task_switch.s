# 1 "task_switch.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "task_switch.S"
# 1 "include/asm.h" 1
# 2 "task_switch.S" 2

.globl task_switch; .type task_switch, @function; .align 0; task_switch:
  push %ebp
  mov %esp, %ebp
  push %esi
  push %edi
  push %ebx

  #call to inner_task_switch
  push 8(%ebp)
  call inner_task_switch
  sub $4, %esp
    pop %ebx
  pop %edi
  pop %esi
movl %eax, %esp

  pop %ebp
  ret
