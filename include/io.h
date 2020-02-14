/*
 * io.h - Definició de l'entrada/sortida per pantalla en mode sistema
 */

#ifndef __IO_H__
#define __IO_H__

#include <types.h>

/** Screen functions **/
/**********************/
#define black 0x0000
#define blue  0x0100
#define green 0x0200
#define cyan  0x0300
#define red   0x0400
#define magenta 0x0500
#define brown 0x0600
#define lightgray 0x0700
#define darkgray 0x0800
#define lightblue 0x0900
#define lightgreen 0x0A00
#define lightcyan 0x0B00
#define lightred 0x0C00
#define lightmagenta 0x0D00
#define yellow 0x0E00
#define white 0x0F00

Byte inb (unsigned short port);
void printc(char c);
void printc_color(char c, short int color);
void printc_xy(Byte x, Byte y, char c);
void printk(char *string);

#endif  /* __IO_H__ */
