#ifndef __MODULES_H__
#define __MODULES_H__

void beep(unsigned int, unsigned int);
void delay(unsigned int);
unsigned char key(void);
void nixie(unsigned char, unsigned char);

extern unsigned char isHold;

#endif