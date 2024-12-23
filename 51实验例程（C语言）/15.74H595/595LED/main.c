#include<reg51.h>
#include<intrins.h>

sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;
void Hc595SendByte(unsigned char dat);
void Delay10ms(unsigned int ) ;
void main()
{
	unsigned char ledNum;
	ledNum=0xfe;
	while(1)
	{
		Hc595SendByte(ledNum);
		ledNum=_cror_(ledNum,1);
		Delay10ms(50);
	}	
}
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
