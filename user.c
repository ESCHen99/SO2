#include <libc.h>


char buff[24];
int time;
int pid;

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    char buffer[256] = {'h', 'o', 'l', 'a'};
    fast_write(1, buffer, 4);
    while(gettime() < 12);
    //write(1, buffer, 3);
    while(1) { 
    }
}
