#include"adc.h"
void Adc()
{
	unsigned int adNum[5],adChannel;
    EA = 0;
	switch(adChannel)
	{
		case 0: 
			Pcf8591SendByte(PCF8591,0x41);
			adNum[0]=Pcf8591ReadByte(PCF8591)*2;  //ADC0 ģ��ת��1  �Ŵ�2����ʾ
			break;  
		
		case 1: 
			Pcf8591SendByte(PCF8591,0x42);
			adNum[1]=Pcf8591ReadByte(PCF8591)*2;  //ADC1  ģ��ת��2
			break;  
		
		case 2: 
			Pcf8591SendByte(PCF8591,0x43);
			adNum[2]=Pcf8591ReadByte(PCF8591)*2;  //ADC2	ģ��ת��3
			break;  
		
		case 3: 
			Pcf8591SendByte(PCF8591,0x40);
			adNum[3]=Pcf8591ReadByte(PCF8591)*2;  //ADC3   ģ��ת��4
			break;  
		
		case 4: 
			Pcf8591DaConversion(PCF8591,0x40, adNum[4]/2); //DAC	  ��ģת��
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
* ������         : Pcf8591SendByte
* ��������		   : д��һ����������
* ����           : addr,dat
* ���         	 : ��
*******************************************************************************/

void Pcf8591SendByte(unsigned char addr,unsigned char dat)
{
	I2cStart();
	I2cSendByte(addr);
	I2cSendByte(dat);
	I2cStop();
}
/*******************************************************************************
* ������         : Pcf8591ReadByte
* ��������		   : ��ȡһ��ת��ֵ
* ����           : addr
* ���         	 : dat
*******************************************************************************/

unsigned char Pcf8591ReadByte(unsigned char addr)
{
	unsigned char dat;
	I2cStart();
	I2cSendByte(addr+1);
	dat=I2cReadByte();
	I2cStop();          //��������
  return dat;
}
/*******************************************************************************
* ������         : Pcf8591DaConversion
* ��������		   : PCF8591����������ģ����
* ����           : addr(AD�ĵ�ַ),dat,value��ת������ֵ��
* ���         	 : ��
*******************************************************************************/

void Pcf8591DaConversion(unsigned char addr,unsigned char dat,unsigned char value)
{
	I2cStart();
	I2cSendByte(addr);
	I2cSendByte(dat);
	I2cSendByte(value);
	I2cStop();	
}