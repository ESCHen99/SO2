#include <asm.h>

ENTRY(load_esp)
  mov 8(%ebp), %esp
  ret
