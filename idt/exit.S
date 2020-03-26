#include <asm.h>

ENTRY(exit)
  push %ebp
  mov %esp, %ebp
  mov $0x01, %eax
  int $0x80
  pop %ebp
  ret
