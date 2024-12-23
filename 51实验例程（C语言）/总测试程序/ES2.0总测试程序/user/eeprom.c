#include"eeprom.h"
unsigned char EpNum;
void Eeprom()
{
	unsigned char n;
	EA=0;
	if(K1==0)
	{
		Delay10ms(1);
		if(K1==0)
			At24c02Write(2,EpNum);
		while((n<50)&&(K1==0))
		{
			n++;
			Delay10ms(1);	
		}			
		n=0;
		n=0;
	}	
	else if(K2==0)
	{
		Delay10ms(1);
		if(K2==0)
			EpNum=At24c02Read(2);
		while((n<50)&&(K2==0))
		{
			n++;
			Delay10ms(1);	
		}			
		n=0;
	}			
	else if(K3==0)
	{
		Delay10ms(1);
		if(K3==0)
			EpNum++;
		while((n<50)&&(K3==0))
		{
			n++;
			Delay10ms(1);	
		}			
		n=0;
		if(EpNum==256)
			EpNum=0;
	}		
	else if(K4==0)
	{
		Delay10ms(1);
		if(K4==0)
			EpNum=0;
		while((n<50)&&(K4==0))
		{
			n++;
			Delay10ms(1);	
		}			
		n=0;
	}			
	DisplayData[0]=0;//千位
	DisplayData[1]=0;//百位
	DisplayData[2]=0;//十位
	DisplayData[3]=0;//个位
	DisplayData[7]=DIG_CODE[EpNum/1000];//千位
	DisplayData[6]=DIG_CODE[EpNum%1000/100];//百位
	DisplayData[5]=DIG_CODE[EpNum%1000%100/10];//个位
	DisplayData[4]=DIG_CODE[EpNum%1000%100%10];
	EA=1;
}
/*******************************************************************************
* 函数名         : void At24c02Write(unsigned char addr,unsigned char dat)
* 函数功能		   : 往24c02的一个地址写入一个数据
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void At24c02Write(unsigned char addr,unsigned char dat)
{
	I2cStart();
	I2cSendByte(0xa0);
	I2cSendByte(addr);
	I2cSendByte(dat);
	I2cStop();
}
/*******************************************************************************
* 函数名         : unsigned char At24c02Read(unsigned char addr)
* 函数功能		   : 读取24c02的一个地址的一个数据
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

unsigned char At24c02Read(unsigned char addr)
{
	unsigned char num;
	I2cStart();
	I2cSendByte(0xa0);
	I2cSendByte(addr);
	I2cStart();
	I2cSendByte(0xa1);
	num=I2cReadByte();
	I2cStop();
	return num;	
}