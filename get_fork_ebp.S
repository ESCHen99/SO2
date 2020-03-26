#include <asm.h>

ENTRY(get_fork_ebp)
  mov %ebp, %eax // This is a pure get current process %ebp
  ret
