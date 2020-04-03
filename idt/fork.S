#include <asm.h>

ENTRY(fork)
  push %ebp
  mov  %esp, %ebp
  mov  $0x02, %eax
  int  $0x80
  cmp  $0, %eax
  jge  fin
  negl %eax
  mov  %eax, errno
  mov $-1, %eax
fin:
  pop  %ebp
  ret
