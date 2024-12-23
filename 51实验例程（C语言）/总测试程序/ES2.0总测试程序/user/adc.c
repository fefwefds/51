#include"adc.h"
void Adc()
{
	unsigned int adNum[5],adChannel;
    EA = 0;
	switch(adChannel)
	{
		case 0: 
			Pcf8591SendByte(PCF8591,0x41);
			adNum[0]=Pcf8591ReadByte(PCF8591)*2;  //ADC0 模数转换1  放大2倍显示
			break;  
		
		case 1: 
			Pcf8591SendByte(PCF8591,0x42);
			adNum[1]=Pcf8591ReadByte(PCF8591)*2;  //ADC1  模数转换2
			break;  
		
		case 2: 
			Pcf8591SendByte(PCF8591,0x43);
			adNum[2]=Pcf8591ReadByte(PCF8591)*2;  //ADC2	模数转换3
			break;  
		
		case 3: 
			Pcf8591SendByte(PCF8591,0x40);
			adNum[3]=Pcf8591ReadByte(PCF8591)*2;  //ADC3   模数转换4
			break;  
		
		case 4: 
			Pcf8591DaConversion(PCF8591,0x40, adNum[4]/2); //DAC	  数模转换
			break;
	}
    EA = 1;
	adNum[4]=adNum[0];
	adChannel++;
	if(adChannel>4)
		adChannel=0;
	LcdWriteCom(0x80);
	LcdWriteData('0'+adNum[0]/1000);	
	LcdWriteData('0'+adNum[0]%1000/100);
	LcdWriteData('0'+adNum[0]%100/10);
	LcdWriteData('0'+adNum[0]%10);
	LcdWriteData(' ');
	LcdWriteData('0'+adNum[1]/1000);	
	LcdWriteData('0'+adNum[1]%1000/100);
	LcdWriteData('0'+adNum[1]%100/10);
	LcdWriteData('0'+adNum[1]%10);
	LcdWriteCom(0x80+0x40);
	LcdWriteData('0'+adNum[2]/1000);	
	LcdWriteData('0'+adNum[2]%1000/100);
	LcdWriteData('0'+adNum[2]%100/10);
	LcdWriteData('0'+adNum[2]%10);
	LcdWriteData(' ');
	LcdWriteData('0'+adNum[3]/1000);	
	LcdWriteData('0'+adNum[3]%1000/100);
	LcdWriteData('0'+adNum[3]%100/10);
	LcdWriteData('0'+adNum[3]%10);											 
}
/*******************************************************************************
* 函数名         : Pcf8591SendByte
* 函数功能		   : 写入一个控制命令
* 输入           : addr,dat
* 输出         	 : 无
*******************************************************************************/

void Pcf8591SendByte(unsigned char addr,unsigned char dat)
{
	I2cStart();
	I2cSendByte(addr);
	I2cSendByte(dat);
	I2cStop();
}
/*******************************************************************************
* 函数名         : Pcf8591ReadByte
* 函数功能		   : 读取一个转换值
* 输入           : addr
* 输出         	 : dat
*******************************************************************************/

unsigned char Pcf8591ReadByte(unsigned char addr)
{
	unsigned char dat;
	I2cStart();
	I2cSendByte(addr+1);
	dat=I2cReadByte();
	I2cStop();          //结束总线
  return dat;
}
/*******************************************************************************
* 函数名         : Pcf8591DaConversion
* 函数功能		   : PCF8591的输出端输出模拟量
* 输入           : addr(AD的地址),dat,value（转换的数值）
* 输出         	 : 无
*******************************************************************************/

void Pcf8591DaConversion(unsigned char addr,unsigned char dat,unsigned char value)
{
	I2cStart();
	I2cSendByte(addr);
	I2cSendByte(dat);
	I2cSendByte(value);
	I2cStop();	
}