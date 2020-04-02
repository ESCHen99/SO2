#include <libc.h>
#include <errno.h>

char buff[24];
int time;
int pid;
int errno = 0;
int fork_comprobar = 0;
struct stats stat;

void perror(void){
    if(errno == 0){
        char message[] = "OK\n";
        write(1, message, 3) ;
    }
    if(errno == EBDFD){
        char message[] = "Bad file descriptor\n";
        write(1, message, strlen(message));
    }
    if(errno == ENULLPTR){
        char message[] = "Null PTR\n";
        write(1, message, strlen(message));
    }
    if(errno == ENEGSIZE){
        char message[] = "Negative size\n";
        write(1, message, strlen(message));
    }
    if(errno == EUNSPECIFIED){
        char message[] = "Unspecified error\n";
        write(1, message, strlen(message));
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
 /*   
    int wait = 200;
    char buffer[256] = "task1\n";
    write(1, buffer, strlen(buffer));
    char buffer2[256] = "task1\n";
//    while(1) fork();
    if(fork() == 0){
      if(fork() == 0){
        char buff3[256] = "task1-child-child\n"; 
        for(int i = 0; i < 5; ++i){
          int aux = gettime();
          while((gettime()-aux) < 200);
          write(1, buff3, strlen(buff3));
        }
        exit();
      }
      char buffer3[256] = "task1-child\n";
      for(int i = 0; i < 5; ++i){
        int aux = gettime();
        while(gettime() - aux < wait);
        ++fork_comprobar;
        write(1, buffer3, strlen(buffer3));
      }
      exit();
    }

    // Testing task switch
    if(getpid() == 0xfefefefe) write(1, buffer2, strlen(buffer2));
    get_stats(getpid(), &stat);
    while(1) {
        int aux = gettime();
        while(gettime() - aux < wait);
        ++fork_comprobar;
        write(1, buffer, strlen(buffer));
    }
*/    
  runjp();
  //runjp_rank(4, 4);
  while(1);
}
