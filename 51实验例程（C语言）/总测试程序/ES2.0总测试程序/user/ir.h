#ifndef __IR_H_
#define __IR_H_

#include<reg51.h>
#include"lcd.h"
sbit IRIN=P3^2;

extern unsigned char code CDIS1[13];
extern unsigned char code CDIS2[13];
extern unsigned char IrValue[6];
extern unsigned char TimeCout;

void IrInit();
void DelayMs(unsigned int );
void IrDisplayDatalay();

#endif