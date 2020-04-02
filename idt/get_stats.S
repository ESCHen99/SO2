#include <asm.h>

ENTRY(get_stats)
  push %ebp
  mov  %esp, %ebp
  push %ebx
  cmp $0 , 8(%ebp) 
  mov 8(%ebp), %ebx
  mov 12(%ebp), %ecx
  mov $0x23, %eax
  int $0x80
  cmp $0, %eax
  jge fin
  negl %eax
  mov %eax, errno
  mov $-1, %eax
fin:
  pop %ebx
  mov %ebp, %esp
  pop %ebp
  ret
