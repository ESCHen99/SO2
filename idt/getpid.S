#include <asm.h>

ENTRY(getpid)
  push %ebp
  mov %esp, %ebp
  mov $20, %eax
  int $0x80
  pop %ebp
  ret
