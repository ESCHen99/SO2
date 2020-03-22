#include <libc.h>
#include <errno.h>

char buff[24];
int time;
int pid;
int errno = 0;

void perror(void){
    if(errno == 0){
        char message[] = "OK\n";
        fast_write(1, message, 3) ;
    }
    if(errno == EBDFD){
        char message[] = "Bad file descriptor\n";
        fast_write(1, message, strlen(message));
    }
    if(errno == ENULLPTR){
        char message[] = "Null PTR\n";
        fast_write(1, message, strlen(message));
    }
    if(errno == ENEGSIZE){
        char message[] = "Negative size\n";
        fast_write(1, message, strlen(message));
    }
    if(errno == EUNSPECIFIED){
        char message[] = "Unspecified error\n";
        fast_write(1, message, strlen(message));
    }
    errno = 0;
}


int __attribute__ ((__section__(".text.main")))
  main(void)
{
    /* ENTREGA 1
    char buffer[256] = "Hola\n";
    perror();                                       // Test no error
    
    if(fast_write(0, buffer, strlen(buffer)) < 0){
        perror();                                   // Test bad file descriptor
    }

    char* buffer2;
    write(1, buffer2, 1);                           // Test null ptr
    write(1, buffer, strlen(buffer));                            
    perror();                                       // Test errno from bad execution after good one
    perror();

    write(1, buffer, -3);
    perror();                                       // Test negative size
        
    while(fast_gettime() < 250);                    // Test gettime()
    while(gettime() < 500)
    while(fast_gettime() < 750);
    while(gettime() < 1000);
    fast_write(1, buffer, 4);
    */


    // Testing task switch
    int wait = 200;
    char buffer[256] = "task1\n";
    write(1, buffer, strlen(buffer));
    char buffer2[256] = "task1\n";
    if(getpid() == 0xfefefefe) write(1, buffer2, strlen(buffer2));
    while(1) {
        int aux = gettime();
        while(gettime() - aux < wait);
        write(1, buffer, strlen(buffer));
    }
}
