#include"key.h"
unsigned char KeyValue;//������Ŷ�ȡ���ļ�ֵ
unsigned char DisplayPlace;
unsigned char DisplayData[8];
unsigned char code DIG_CODE[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//0~9����ܶ���
unsigned char	DigDisplayOn;
/*******************************************************************************
* ������         : KeyDown
* ��������		   : ����а������²���ȡ��ֵ
* ����           : ��
* ���         	 : ��
*******************************************************************************/


void KeyDown(void)
{
	unsigned int a;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)
	{
		Delay10ms(1);
		if(GPIO_KEY!=0x0f)
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
				Delay10ms(1);
				a++;
			}
			a=0;
		}
	}
}
/*******************************************************************************
* ������         : Delay10ms
* ��������		   : ��ʱ��������ʱ10ms
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void Delay10ms(unsigned int c)   //��� 0us
{
    unsigned char a,b;
    for(;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}

/*******************************************************************************
* ������         : TimerConfiguration
* ��������		   : ��ʱ����ʼ��
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void Timer0Configuration()
{
	TMOD=0X02;//ѡ��Ϊ��ʱ��ģʽ��������ʽ2������TRX��������

	TH0=0X9c;	//����ʱ��0����ֵ����ʱ100us
	TL0=0X9c;	
	ET0=1;//�򿪶�ʱ��0�ж�����
	EA=1;//�����ж�
	TR0=1;//�򿪶�ʱ��			
}
/*******************************************************************************
* ������         : Timer() interrupt 1
* ��������		   : ��ʱ��0���жϺ���
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void Timer0() interrupt  1 
{
	KeyDown();	//���̼��
	if(DigDisplayOn)
	{
		GPIO_DIG=0x00;//����
	switch(DisplayPlace)	 //λѡ��ѡ�����������ܣ�
	{
		case(0):
			LSA=0;LSB=0;LSC=0; break;
		case(1):
			LSA=1;LSB=0;LSC=0; break;
		case(2):
			LSA=0;LSB=1;LSC=0; break;
		case(3):
			LSA=1;LSB=1;LSC=0; break;
		case(4):
			LSA=0;LSB=0;LSC=1; break;
		case(5):
			LSA=1;LSB=0;LSC=1; break;
		case(6):
			LSA=0;LSB=1;LSC=1; break;
		case(7):
			LSA=1;LSB=1;LSC=1; break;	
	}
	GPIO_DIG=DisplayData[DisplayPlace];
	DisplayPlace++;
	if(DisplayPlace>7)
		DisplayPlace=0;
	}
	
}

