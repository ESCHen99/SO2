#include <asm.h>

ENTRY(task_switch)
  push %ebp
  mov %esp, %ebp
  push %esi
  push %edi
  push %ebx

  #call to inner_task_switch
  push %ebp
  push 8(%ebp)
  call inner_task_switch
  add  $8, %esp

  
  pop  %ebx
  pop  %edi
  pop  %esi
  
  movl %eax, %esp

  pop  %ebp
  ret
