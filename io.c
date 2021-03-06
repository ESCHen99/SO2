/*
 * io.c - 
 */

#include <io.h>

#include <types.h>

/**************/
/** Screen  ***/
/**************/

#define NUM_COLUMNS 80
#define NUM_ROWS    25

Byte x, y=19;

/* Read a byte from 'port' */
Byte inb (unsigned short port)
{
  Byte v;

  __asm__ __volatile__ ("inb %w1,%0":"=a" (v):"Nd" (port));
  return v;
}


void printc_color(char c, short int color)
{
     __asm__ __volatile__ ( "movb %0, %%al; outb $0xe9" ::"a"(c)); /* Magic BOCHS debug: writes 'c' to port 0xe9 */
  if (c=='\n')
  {
    x = 0;
    Word *screen = (Word *)0xb8000;

    if(y + 1 >= NUM_ROWS)
      for(int i = 1; i < NUM_ROWS; ++i){
	  	for(int j = 0; j < NUM_COLUMNS; ++j){
			screen[(i-1) * NUM_COLUMNS + j] = screen[i * NUM_COLUMNS + j];
            if( i == NUM_ROWS - 1) screen[i * NUM_COLUMNS + j] = 0;
		}
	  }
      else ++y;
  }
  else
  {
    Word ch = (Word) (c & 0x00FF) | color; 
	Word *screen = (Word *)0xb8000;
	screen[(y * NUM_COLUMNS + x)] = ch;
    if (++x >= NUM_COLUMNS)
    {
      if(y + 1 >= NUM_ROWS)
      for(int i = 1; i < NUM_ROWS; ++i){
	  	for(int j = 0; j < NUM_COLUMNS; ++j){
			screen[(i-1) * NUM_COLUMNS + j] = screen[i * NUM_COLUMNS + j];
            if( i == NUM_ROWS - 1) screen[i * NUM_COLUMNS + j] = 0;
		}
	  }
      else ++y; 
      x = 0;
    }
  }
}

void printc(char c)
{
    printc_color(c, cyan);
}

void printc_xy(Byte mx, Byte my, char c)
{
  Byte cx, cy;
  cx=x;
  cy=y;
  x=mx;
  y=my;
  printc(c);
  x=cx;
  y=cy;
}

void printk(char *string)
{
  int i;
  for (i = 0; string[i]; i++)
    printc_color(string[i], red);
}

void printkn(int n){
    if(n < 10){
      printc_color('0' + n, white);
    }
    else{
      printkn(n/10);
      printkn((n)%10);
    }        
}
