#include"include.h"

#define GPIO_LED P2

sbit BUZZER=P1^5;
sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;
sbit PWM=P2^1;
bit DIR;

void Eeror();
void Beep();
void LcdDisplayDatalay(int );
void Hc595SendByte(unsigned char dat);
void Time1Config();
void DigDisplay(void);
void delaydz(unsigned int time);
void DZmain(void);

void AD_Main(void);
void DA_Main(void);


uint temp,count;
unsigned int countda,value,timer1;
unsigned char countdz,num=0x01;

/*******************************************************************************
* 函数名         : main
* 函数功能		   : 主函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void main()
{	
	unsigned char LedData, m;
    unsigned int mainTime;
//    long x, y;
//	DZmain();
	Timer0Configuration();
	Ds1302Init();
	LedData=0xfe;

	while(1)
	{
        DigDisplayOn = 0;
		EX0 = 0;
        LcdInit();

		switch(KeyValue)
		{
            //0是LED灯
			case(0):
			    while(1)
                {
                    mainTime++;
                    if(mainTime > 0x0DFF)
                    {
                        mainTime = 0;
                        GPIO_LED = LedData; 
    				    LedData = _cror_(LedData, 1);//将GPIO_LED左移一位   
                    }
                    if(KeyValue != 0)
                    {
                        break;
                    }
                }                
				break;
            //1是步进电机
			case(1):
				while(1)
                {
            	    EA = 0;
                    Motor();    
                    EA = 1;
                    if(KeyValue != 1)
                    {
                        break;
                    }    
                } 
			
				break;
            //2是蜂鸣器
			case(2):
			    while(1)
                {
                    Beep();
                    if(KeyValue != 2)
                    {
                        break;
                    }    
                }				
				break;
            //3是DS1302
			case(3):
                DigDisplayOn = 1;
                while(1)
                {
                    mainTime++;
                    if(mainTime > 0xFF)
                    {
        				Ds1302ReadTime();
        				DisplayData[0] = DIG_CODE[TIME[0]&0x0f];
        				DisplayData[1] = DIG_CODE[TIME[0]>>4];
        				DisplayData[2] = 0X40;
        				DisplayData[3] = DIG_CODE[TIME[1]&0x0f];
        				DisplayData[4] = DIG_CODE[TIME[1]>>4];
        				DisplayData[5] = 0X40;
        				DisplayData[6] = DIG_CODE[TIME[2]&0x0f];
        				DisplayData[7] = DIG_CODE[TIME[2]>>4];
                    }
                    if(KeyValue != 3)
                    {
                        break;
                    }
                }
				       break;
            //4是18B20
			case(4):
				EA=0;
                while(1)
                {
            				Ds18b20ChangTemp();
            				LcdDisplayDatalay(Ds18b20ReadTemp());
                    if(KeyValue != 4)
                    {
						EA=1;
                        break;
                    }
                }
				        break;
            //5是红外遥控
			case(5):
                  IrInit();
                  LcdWriteCom(0x80);
            			for(m=0;m<13;m++)
            			{
            				LcdWriteData(CDIS1[m]);	
            			}
            			LcdWriteCom(0x80+0x40);
            			for(m=0;m<9;m++)
            			{
            				LcdWriteData(CDIS2[m]);	
            			}
                  while(1)
                  {
                      if(KeyValue != 5)
                      {
                          break;
                      }    
                  }
                  break;
            //6是24C02
			case(6):
				DigDisplayOn=1;
                while(1)
                {
                    Eeprom();
                    if(KeyValue != 6)
                    {
                        break;
                    }
                }				
				break;
            //7是ADC
			case(7):
			
			    while(1)
                {    			
    				AD_Main();
                    if(KeyValue != 7)
                    {
                        break;
                    }
                }
				break;
            //8是595LED
			case(8):
			    while(1)
                {				
					mainTime++;
                    if(mainTime > 0x0DFF)
                    {
                        mainTime = 0;
                        Hc595SendByte(LedData);
				        LedData=_cror_(LedData,1);   
                    } 
					if(KeyValue != 8)
                    {
                        break;
                    }				                                       
                }
				break;
            //9是彩屏
			case(9):				
				
				TFT_Init();	
				EA = 0;
				TFT_ClearScreen(BLUE);               
				GUI_Write32CnChar(22,0,"普中科技",RED,BLUE);	
				GUI_Line(22,29,154,29,RED);
				GUI_Line(22,31,154,31,RED);
               // TOUCH_Adjust();
                EA = 1;
                while(1)
                {
//                    if(TOUCH_XPT_ReadXY() == 1)
//                    {
//                        x = xpt_xy.x * TouchAdj.xFactor / LCD_ADJ_MUX + TouchAdj.xOffset;
//                        y = xpt_xy.y * TouchAdj.yFactor / LCD_ADJ_MUX + TouchAdj.yOffset;
//                        if (x > 175 )
//            			{
//            				x = 175;
//            			}
//            
//            			if (y > 219)
//            			{
//            				y = 219;
//            			}
//                        GUI_Dot((uint)x , (uint)y, BLUE);
//                    }
                    KeyValue = 0;
                    if(KeyValue != 9)
                    {
                        break;
                    }
                }
				break;
			//DA输出
			case(10):
				Time1Config();
				while(1)
				{
				 DA_Main();
				 if(KeyValue != 10)
                    {
                       
						TR1 = 0;
						ET1 = 0;
						break;
                    }
				}
				break;
			case(11):
				while(1)
				{
					//EA=0;
					DZmain();
				//	EA=1;
					if(KeyValue != 11)
                    {
						break;
					}						
				}
				break;
		

            //其他是错误
			default:
				while(1)
                {					
                    Eeror();
                    if(KeyValue < 12)
                    {
                        break;
                    }    
                }				
				break;					
		}
	}
}
/*******************************************************************************
* 函数名         : LcdDisplayDatalay()
* 函数功能		   : LCD显示读取到的温度
* 输入           : v
* 输出         	 : 无
*******************************************************************************/

void LcdDisplayDatalay(int temp) 	 //lcd显示
{
    
  unsigned char datas[] = {0, 0, 0, 0, 0}; //定义数组
	float tp;
//	LcdInit();			 //初始化LCD
	if(temp< 0)				//当温度值为负数
  {
  	LcdWriteCom(0x80);		//写地址 80表示初始地址
    LcdWriteData('-');  		//显示负
		//因为读取的温度是实际温度的补码，所以当温度为负数的时候，要将它转换为实际温度
		temp=~temp;
		temp=temp+1;//将读取到的温度值取反再加1
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算加上0.5，还是在小数点后面。
 
  }
  else
  {			
  	LcdWriteCom(0x80);		//写地址 80表示初始地址
    LcdWriteData('+'); 		//显示正
		tp=temp;//因为数据处理有小数点所以将温度赋给一个浮点型变量
		//如果温度是正的那么，那么正数的补码就是它本身
		temp=tp*0.0625*100+0.5;	
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算加上0.5，还是在小数点后面。
  }
	datas[0] = temp / 10000;
  datas[1] = temp % 10000 / 1000;
  datas[2] = temp % 1000 / 100;
  datas[3] = temp % 100 / 10;
  datas[4] = temp % 10;
 
	LcdWriteCom(0x82);		  //写地址 80表示初始地址
  LcdWriteData('0'+datas[0]); //百位 


  LcdWriteCom(0x83);		 //写地址 80表示初始地址
  LcdWriteData('0'+datas[1]); //十位

	LcdWriteCom(0x84);		//写地址 80表示初始地址
  LcdWriteData('0'+datas[2]); //个位 

	LcdWriteCom(0x85);		//写地址 80表示初始地址
  LcdWriteData('.'); 		//显示 ‘.’

	LcdWriteCom(0x86);		 //写地址 80表示初始地址
  LcdWriteData('0'+datas[3]); //显示小数点  

	LcdWriteCom(0x87);		 //写地址 80表示初始地址
  LcdWriteData('0'+datas[4]); //显示小数点  

	LcdWriteCom(0x88);		//写地址 80表示初始地址
  LcdWriteData('C');   
}

void Eeror()
{
	LcdWriteCom(0x80);
	LcdWriteData('E');
	LcdWriteData('E');	
	LcdWriteData('R');	
	LcdWriteData('O');	
	LcdWriteData('R');	
	LcdWriteData('!');			
}
/*******************************************************************************
* 函数名         : Beep()
* 函数功能		   : 蜂鸣器响
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void Beep()
{
	unsigned char i;
	BUZZER=0;
	for(i=50;i>0;i--);
	BUZZER=1;
	for(i=50;i>0;i--);
}
/*******************************************************************************
* 函数名         : Hc595SendByte(unsigned char dat)
* 函数功能		   : 想74H595发送一个字节的数据
* 输入           : 无
* 输出         	 : 无
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
void DigDisplay(void)
{
	unsigned char i;
	unsigned int j;
	for(i=0;i<8;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位	
		}
		GPIO_DIG=DisplayData[i];//发送段码
		j=50;						 //扫描间隔时间设定
		while(j--);	
		GPIO_DIG=0x00;//消隐
	}
}
void AD_Main(void)
{

	  EA=0;
	  if(count==50)
	  {
	  	count=0; 
		temp = Read_AD_Data(0x94);		//   AIN0 电位器
	//	temp = Read_AD_Data(0xD4);		//   AIN1 热敏电阻
	//	temp = Read_AD_Data(0xA4);		//   AIN2 光敏电阻
	//	temp = Read_AD_Data(0xE4);		//   AIN3 外部输入
	  }
	  count++;
	  
	  DisplayData[7]=DIG_CODE[0];
	  DisplayData[6]=DIG_CODE[0];
	  DisplayData[5]=DIG_CODE[0];
	  DisplayData[4]=DIG_CODE[0];

	  DisplayData[3]=DIG_CODE[temp%10000/1000];
	  DisplayData[2]=DIG_CODE[temp%1000/100];
	  DisplayData[1]=DIG_CODE[temp%100/10];
	  DisplayData[0]=DIG_CODE[temp%10/1];

	  DigDisplay();
	  EA=1;
	
}
void Time1Config()
{
	TMOD|= 0x10;   //设置定时计数器工作方式1为定时器

	//--定时器赋初始值，12MHZ下定时1us--//  
	TH1 = 0xFF; 
	TL1 = 0xff;

	
	ET1 = 1; 	 //开启定时器1中断
	EA = 1;
	TR1 = 1;	 //开启定时器	
}
/*******************************************************************************
* 函 数 名       : Time1
* 函数功能		 : 定时器1的中断函数
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/

void Time1(void) interrupt 3    //3 为定时器1的中断号  1 定时器0的中断号 0 外部中断1 2 外部中断2  4 串口中断
{
	TH1 = 0xFF;  //重新赋初值
	TL1 = 0xFf;
	timer1++; 
    countda++;
	
}
void DA_Main(void)
{  
		if(countda>100)							
		{  
			countda=0;
			if(DIR==1)					   //DIR控制增加或减小
			{
			  value++;
			}			
			if(DIR==0)
			{
			  value--;
			}
				
		}

		if(value==1000)
		{
		  DIR=0;
		}
		if(value==0)
		{
		  DIR=1;
		}	
				
		if(timer1>1000)  //PWM周期为100*1us
		{
			timer1=0;
		}
		if(timer1 <value)	
		{
			PWM=1;
		}
		else
		{
			PWM=0;
		}
 }


void delaydz(unsigned int time)
{
  unsigned int i,j;
  for(i=0;i<time;i++)
    for(j=0;j<121;j++)
	{
		if(KeyValue != 11)break;
	}
}

void DZmain(void)
{ 
		num=0x01;
		for(countdz=0;countdz<8;countdz++)
		{			
			P0=~num;
			Hc595SendByte(0xff);
			num<<=1;			
			delaydz(40);
		}
		num=0x01;
		for(countdz=0;countdz<8;countdz++)
		{
			
			P0=0x00;
			Hc595SendByte(num);
			num<<=1;		
			delaydz(40);
		}
	 
}
