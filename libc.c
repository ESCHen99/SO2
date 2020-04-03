/*
 * libc.c 
 */

#include <libc.h>

#include <types.h>

#include <errno.h>


int errno;

void itoa(int a, char *b)
{
  int i, i1;
  char c;
  
  if (a==0) { b[0]='0'; b[1]=0; return ;}
  
  i=0;
  while (a>0)
  {
    b[i]=(a%10)+'0';
    a=a/10;
    i++;
  }
  
  for (i1=0; i1<i/2; i1++)
  {
    c=b[i1];
    b[i1]=b[i-i1-1];
    b[i-i1-1]=c;
  }
  b[i]=0;
}

int strlen(char *a)
{
  int i;
  
  i=0;
  
  while (a[i]!=0) i++;
  
  return i;
}

void perror(void){
    if(errno == 0){
        char message[] = "OK\n";
        write(1, message, 3) ;
    }
    if(errno == EBADFD){
        char message[] = "Bad file descriptor\n";
        write(1, message, strlen(message));
    }
    if(errno == ENOMEM){
        char message[] = "ENOMEM\n";
        write(1, message, strlen(message));
     }
     if(errno == EINVAL){
        char message[] = "EINVAL\n";
        write(1, message, strlen(message));
     }
    if(errno == ESRCH){
        char message[] = "ESRCH\n";
        write(1, message, strlen(message));
     }
    if(errno == EFAULT){
        char message[] = "EFAULT\n";
        write(1, message, strlen(message));
     }
    errno = 0;
}
