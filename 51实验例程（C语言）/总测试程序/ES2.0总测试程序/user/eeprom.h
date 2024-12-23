#ifndef __EEPROM_H_
#define __EEPROM_H_

#include<reg51.h>
#include"i2c.h"
#include"key.h"

sbit K1=P3^1;
sbit K2=P3^0;
sbit K3=P3^2;
sbit K4=P3^3;

void At24c02Write(unsigned char ,unsigned char );
unsigned char At24c02Read(unsigned char );
void Eeprom();
#endif