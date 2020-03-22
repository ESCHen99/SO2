#include <asm.h>

ENTRY(load_esp)
  mov 4(%esp), %esp
  ret
