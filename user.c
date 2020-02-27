#include <libc.h>
#include <errno.h>

char buff[24];
int time;
int pid;
int errno = 0;

void perror(void){
    if(errno == 0){
        char message[] = "OK.";
        write(1, message, 3) ;
    }
    if(errno == BADFD){
        char message[] = "Bad file descriptor\n";
        write(1, message, 20);
    }
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
    char buffer[256] = "hola";
    perror();
    fast_write(0, buffer, 5);
    write(1, buffer, 4);
    write(0, buffer, 4);
    perror();
    write(1, buffer, 4);
    //perror();
    write(1, buffer, 4);
    //perror();
    //while(gettime() < 12);
    //fast_write(1, buffer, 4);
    while(1) { 
    }
}
