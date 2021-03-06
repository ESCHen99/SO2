#include <asm.h>
#include <segment.h>

ENTRY(sys_call_table)
    .long sys_ni_syscall
    .long sys_exit
    .long sys_fork
    .long sys_ni_syscall
    .long sys_write
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_gettime
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_getpid
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_ni_syscall
    .long sys_get_stats


.globl MAX_SYSCALL
MAX_SYSCALL = (. - sys_call_table)/4
