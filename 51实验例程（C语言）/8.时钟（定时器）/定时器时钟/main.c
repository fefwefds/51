/*******************************************************************************
* ʵ����			   : ��ʱ��ʵ��
* ʹ�õ�IO	     : 
* ʵ��Ч��       :1602��ʾʱ�ӣ���K3����ʱ�����ã���K1ѡ�����õ�ʱ���룬��K2ѡ��
*ѡ�����ü�1�� 
*	ע��					 ��
*******************************************************************************/
#include<reg51.h>	
#include"lcd.h"
sbit K1=P3^0;
sbit K2=P3^1;
sbit K3=P3^2;
sbit K4=P3^3;

unsigned char Time;
//������ʱ���ֵ

void Delay1ms(unsigned int c);
void TimerConfiguration();
void Int0Configuration();

unsigned char SetPlace;
 
/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void main(void)
{
	unsigned char hour,minit,second;
	unsigned int i;
	TimerConfiguration();
	Int0Configuration();
	LcdInit();
	hour=12;
	LcdWriteData('0'+hour/10);
	LcdWriteData('0'+hour%10);
	LcdWriteData('-');
	LcdWriteData('0'+minit/10);
	LcdWriteData('0'+minit%10);
	LcdWriteData('-');
	LcdWriteData('0'+second/10);
	LcdWriteData('0'+second%10);
	while(1)
	{
		if(TR0==0)
		{
			if(K1==0)		//��ⰴ��K2�Ƿ���
			{
				Delay1ms(10);	//��������
				if(K1==0)
				{
					SetPlace++;
					if(SetPlace>=3)
						SetPlace=0;					
				}

				while((i<50)&&(K1==0))	 //��ⰴ���Ƿ��ɿ�
				{
					Delay1ms(1);
					i++;
				}
				i=0;
			}
			if(K2==0)		//��ⰴ��K3�Ƿ���
			{
				Delay1ms(10);	//��������
				if(K2==0)
				{
					if(SetPlace==0)
					{
						second++;
						if(second>=60)
							second=0;
					}
					else if(SetPlace==1)
					{
						minit++;
						if(minit>=60)
							minit=0;	
					}
					else
					{
						hour++;
						if(hour>=24)
							hour=0;
					}				
				}

				while((i<50)&&(K2==0))	 //��ⰴ���Ƿ��ɿ�
				{
					Delay1ms(1);
					i++;
				}
				i=0;
			}
		}	
		if(Time>=20)	 //һ���������ı���ֵ
		{
			Time=0;
			second++;
			if(second==60)
			{
				second=0;
				minit++;
				if(minit==60)
				{
					minit=0;
					hour++;
					if(hour==24)
					{
						hour=0;	
					}
				}				
			}					
		}	
	    //--��ʾʱ��--//
		LcdWriteCom(0x80);
		LcdWriteData('0'+hour/10);
		LcdWriteData('0'+hour%10);
		LcdWriteCom(0x83);
		LcdWriteData('0'+minit/10);
		LcdWriteData('0'+minit%10);
		LcdWriteCom(0x86);
		LcdWriteData('0'+second/10);
		LcdWriteData('0'+second%10);
	
	}				
}
/*******************************************************************************
* �� �� ��       : Delay1ms()
* ��������		 : ��ʱ1ms
* ��    ��       : c
* ��    ��       : ��
*******************************************************************************/		   

void Delay1ms(unsigned int c)   //��� 0us
{
    unsigned char a,b;
	for (; c>0; c--)
	{
		for(b=199;b>0;b--)
		{
			for(a=1;a>0;a--);
		}
        
	}
    
}

/*******************************************************************************
* �� �� ��         : TimerConfiguration()
* ��������		   : ���ö�ʱ��ֵ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/		   

void TimerConfiguration()
{
    TMOD = 0x01; //ѡ������ʽ1
    TH0 = 0x3C;	 //���ó�ʼֵ
    TL0 = 0x0B0; 
    EA = 1;			 //�����ж�
    ET0 = 1;		 //�򿪶�ʱ��0�ж�
    TR0 = 1;		 //������ʱ��0
}
/*******************************************************************************
* �� �� ��         : Timer0()
* ��������		   : ��ʱ��0�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/		   

void Timer0() interrupt 1
{
	  TH0 = 0x3C;	 //���ó�ʼֵ
    TL0 = 0x0B0;
		Time++;
}
/*******************************************************************************
* �� �� ��         : Int0Configuration()
* ��������		   : �����ⲿ�ж�0
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/		   

void Int0Configuration()
{
	//����INT0
	IT0=1;//�����س�����ʽ���½��أ�
	EX0=1;//��INT0���ж�����
	EA=1;//�����ж�	
}
/*******************************************************************************
* �� �� ��         : Int0() interrupt 0
* ��������		   : �ⲿ�ж�0���жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/		   

void Int0() interrupt 0		 
{
	Delay1ms(10);
	if(K3==0)
	{
		TR0=~TR0;
		SetPlace=0;
	}
}
