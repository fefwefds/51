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
	DisplayData[0]=0;//ǧλ
	DisplayData[1]=0;//��λ
	DisplayData[2]=0;//ʮλ
	DisplayData[3]=0;//��λ
	DisplayData[7]=DIG_CODE[EpNum/1000];//ǧλ
	DisplayData[6]=DIG_CODE[EpNum%1000/100];//��λ
	DisplayData[5]=DIG_CODE[EpNum%1000%100/10];//��λ
	DisplayData[4]=DIG_CODE[EpNum%1000%100%10];
	EA=1;
}
/*******************************************************************************
* ������         : void At24c02Write(unsigned char addr,unsigned char dat)
* ��������		   : ��24c02��һ����ַд��һ������
* ����           : ��
* ���         	 : ��
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
* ������         : unsigned char At24c02Read(unsigned char addr)
* ��������		   : ��ȡ24c02��һ����ַ��һ������
* ����           : ��
* ���         	 : ��
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