/*******************************************************************************
* ʵ �� ��		 : �������ʵ��
* ʹ�õ�IO	     : �����ʹ��P0,����ʹ��P3.0��P3.1��P3.2��P3.3
* ʵ��Ч��       : ��������̷ֱ���ʾ�������������ʾʮ�����Ƶ�0��F��
* ע    ��		 ��
*******************************************************************************/
#include<reg51.h>

#define GPIO_DIG P0
#define GPIO_KEY P1

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

unsigned char code DIG_CODE[17]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//0��1��2��3��4��5��6��7��8��9��A��b��C��d��E��F����ʾ��
unsigned char KeyValue;
//������Ŷ�ȡ���ļ�ֵ
void Delay10ms();   //��ʱ10ms
void KeyDown();		 //��ⰴ������
 
/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void main(void)
{
	LSA=0; //��һ��������ṩλѡ
	LSB=0;
	LSC=0;
	while(1)
	{
		KeyDown();
		GPIO_DIG=DIG_CODE[KeyValue];
	}				
}
/*******************************************************************************
* �� �� ��         : KeyDown
* ��������		   : ����а������²���ȡ��ֵ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void KeyDown(void)
{
	char a=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//��ȡ�����Ƿ���
	{
		Delay10ms();//��ʱ10ms��������
		if(GPIO_KEY!=0x0f)//�ٴμ������Ƿ���
		{
			
			//������
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			//������
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			while((a<50)&&(GPIO_KEY!=0xf0))	 //��ⰴ�����ּ��
			{
				Delay10ms();
				a++;
			}
		}
	}
}
/*******************************************************************************
* �� �� ��         : Delay10ms
* ��������		   : ��ʱ��������ʱ10ms
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Delay10ms(void)   //��� 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}