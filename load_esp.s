# 1 "load_esp.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "load_esp.S"
# 1 "include/asm.h" 1
# 2 "load_esp.S" 2

.globl load_esp; .type load_esp, @function; .align 0; load_esp:
  mov 4(%esp), %esp
  ret
