# 1 "get_current_ebp.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "get_current_ebp.S"
# 1 "include/asm.h" 1
# 2 "get_current_ebp.S" 2

.globl get_current_ebp; .type get_current_ebp, @function; .align 0; get_current_ebp:
  mov (%ebp), %eax
  ret
