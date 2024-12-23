#include"key.h"
unsigned char KeyValue;//用来存放读取到的键值
unsigned char DisplayPlace;
unsigned char DisplayData[8];
unsigned char code DIG_CODE[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//0~9数码管段码
unsigned char	DigDisplayOn;
/*******************************************************************************
* 函数名         : KeyDown
* 函数功能		   : 检测有按键按下并读取键值
* 输入           : 无
* 输出         	 : 无
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
			
			//测试列
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			//测试行
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			while((a<50)&&(GPIO_KEY!=0xf0))	 //检测按键松手检测
			{
				Delay10ms(1);
				a++;
			}
			a=0;
		}
	}
}
/*******************************************************************************
* 函数名         : Delay10ms
* 函数功能		   : 延时函数，延时10ms
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Delay10ms(unsigned int c)   //误差 0us
{
    unsigned char a,b;
    for(;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}

/*******************************************************************************
* 函数名         : TimerConfiguration
* 函数功能		   : 定时器初始化
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Timer0Configuration()
{
	TMOD=0X02;//选择为定时器模式，工作方式2，仅用TRX打开启动。

	TH0=0X9c;	//给定时器0赋初值，定时100us
	TL0=0X9c;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器			
}
/*******************************************************************************
* 函数名         : Timer() interrupt 1
* 函数功能		   : 定时器0的中断函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Timer0() interrupt  1 
{
	KeyDown();	//键盘检测
	if(DigDisplayOn)
	{
		GPIO_DIG=0x00;//消隐
	switch(DisplayPlace)	 //位选，选择点亮的数码管，
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

