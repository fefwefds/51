#ifndef __DS1302_H_
#define __DS1302_H_

#include<reg51.h>
#include<intrins.h>

//ds1302IO
sbit DSIO=P3^4;
sbit RST=P3^5;
sbit SCLK=P3^6;
extern unsigned char TIME[6];	//加入全局变量

void Ds1302WriteByte(unsigned char dat);
unsigned char Ds1302ReadByte();
void Ds1302Write(unsigned char addr,unsigned dat);
unsigned char Ds1302Read(unsigned char addr);
void Ds1302Init();
void Ds1302ReadTime();

#endif