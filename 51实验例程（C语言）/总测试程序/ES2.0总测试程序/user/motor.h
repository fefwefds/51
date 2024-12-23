#ifndef __MOTOR_H_
#define __MOTOR_H_

#include<reg51.h>
#define GPIO_MOTOR P1

extern unsigned char code FFW[8];

void Delay(unsigned int );
void  Motor();

#endif