#include <asm.h>

ENTRY(get_fork_ebp)
  mov %ebp, %eax
  ret
