#include <asm.h>

ENTRY(fork)
  push %ebp
  mov  %esp, %ebp
  mov  $0x02, %eax
  int  $0x80
  pop  %ebp
  ret
