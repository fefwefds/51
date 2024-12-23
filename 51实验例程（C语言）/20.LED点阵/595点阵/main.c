#include"reg51.h"
#include<intrins.h>

sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;

/*******************************************************************************
* ������         : Hc595SendByte(unsigned char dat)
* ��������		   : ��74H595����һ���ֽڵ�����
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void Hc595SendByte(unsigned char dat)
{
	unsigned char a;
	SRCLK=0;
	RCLK=0;
	for(a=0;a<8;a++)
	{
		SER=dat>>7;
		dat<<=1;

		SRCLK=1;
		_nop_();
		_nop_();
		SRCLK=0;	
	}

	RCLK=1;
	_nop_();
	_nop_();
	RCLK=0;
}
/*******************************************************************************
* ������         : Delay10ms
* ��������		   : ��ʱ��������ʱ10ms
* ����           : c
* ���         	 : ��
*******************************************************************************/
void Delay10ms(unsigned int c)   //��� 0us
{
    unsigned char a,b;
    for(;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}
void main(void)
{
	unsigned char i,num;
   while(1)
   {
   		num=0x01;
   		for(i=0;i<8;i++)
		{
		  	P0=~num;
			Hc595SendByte(0xff);
			num<<=1;
			Delay10ms(50);
		}
   		num=0x01;
   		for(i=0;i<8;i++)
		{		  	
			Hc595SendByte(num);
			P0=0x00;
			num<<=1;
			Delay10ms(50);
		}
   
   }
}