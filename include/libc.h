/*
 * libc.h - macros per fer els traps amb diferents arguments
 *          definició de les crides a sistema
 */
 
#ifndef __LIBC_H__
#define __LIBC_H__

#include <stats.h>

int getpid(void);

int fork(void);

int write(int fd, char *buffer, int size);

int fast_write(int fd, char *buffer, int size);

int get_stats(int pid, struct stats *st);

int gettime(void);

int fast_gettime(void);

void perror(void);

void itoa(int a, char *b);

int strlen(char *a);

int getpid();

int fork();

void exit();

#endif  /* __LIBC_H__ */
