#ifndef __ADC_H_
#define __ADC_H_

#include<reg51.h>
#include"i2c.h"
#include"lcd.h"
#define  PCF8591 0x90

void Pcf8591SendByte(unsigned char addr,unsigned char dat);
unsigned char Pcf8591ReadByte(unsigned char addr);
void Pcf8591DaConversion(unsigned char addr,unsigned char dat,unsigned char value);
void Adc();
#endif