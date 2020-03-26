#include <asm.h>

ENTRY(get_current_ebp)
  mov (%ebp), %eax // We want (%ebp) since %ebp lonely corresponds to the inner_task_switch and not task_switch
  ret
