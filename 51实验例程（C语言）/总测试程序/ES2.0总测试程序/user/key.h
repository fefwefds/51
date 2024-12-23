#ifndef __KEY_H_
#define __KEY_H_

#include<reg51.h>
#define GPIO_KEY P1
#define GPIO_DIG P0
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//extern unsigned char DisplayPlace;
extern unsigned char DisplayData[8];
extern unsigned char code DIG_CODE[10];
extern unsigned char	DigDisplayOn;
extern unsigned char KeyValue;//用来存放读取到的键值

void KeyDown();
void Delay10ms(unsigned int );
void Timer0Configuration();


#endif