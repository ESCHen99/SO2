#include <asm.h>

ENTRY(get_stats)
  push %ebp
  mov  %esp, %ebp
  push %ebx
  
  mov 8(%ebp), %ebx
  mov 12(%ebp), %ecx
  mov $0x23, %eax
  int $0x80

  pop %ebx
  mov %ebp, %esp
  pop %ebp
  ret
