#include <libc.h>

char buff[24];
int time;
int pid;
int fork_comprobar = 0;



int __attribute__ ((__section__(".text.main")))
  main(void)
{
  runjp(); // Joc de proves E2
  while(1);
}
