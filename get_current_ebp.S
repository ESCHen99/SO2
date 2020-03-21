#include <asm.h>

ENTRY(get_current_ebp)
  mov %ebp, %eax
  ret
