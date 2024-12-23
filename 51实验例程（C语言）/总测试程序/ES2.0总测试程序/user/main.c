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
* ������         : main
* ��������		   : ������
* ����           : ��
* ���         	 : ��
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
            //0��LED��
			case(0):
			    while(1)
                {
                    mainTime++;
                    if(mainTime > 0x0DFF)
                    {
                        mainTime = 0;
                        GPIO_LED = LedData; 
    				    LedData = _cror_(LedData, 1);//��GPIO_LED����һλ   
                    }
                    if(KeyValue != 0)
                    {
                        break;
                    }
                }                
				break;
            //1�ǲ������
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
            //2�Ƿ�����
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
            //3��DS1302
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
            //4��18B20
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
            //5�Ǻ���ң��
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
            //6��24C02
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
            //7��ADC
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
            //8��595LED
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
            //9�ǲ���
			case(9):				
				
				TFT_Init();	
				EA = 0;
				TFT_ClearScreen(BLUE);               
				GUI_Write32CnChar(22,0,"���пƼ�",RED,BLUE);	
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
			//DA���
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
		

            //�����Ǵ���
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
* ������         : LcdDisplayDatalay()
* ��������		   : LCD��ʾ��ȡ�����¶�
* ����           : v
* ���         	 : ��
*******************************************************************************/

void LcdDisplayDatalay(int temp) 	 //lcd��ʾ
{
    
  unsigned char datas[] = {0, 0, 0, 0, 0}; //��������
	float tp;
//	LcdInit();			 //��ʼ��LCD
	if(temp< 0)				//���¶�ֵΪ����
  {
  	LcdWriteCom(0x80);		//д��ַ 80��ʾ��ʼ��ַ
    LcdWriteData('-');  		//��ʾ��
		//��Ϊ��ȡ���¶���ʵ���¶ȵĲ��룬���Ե��¶�Ϊ������ʱ��Ҫ����ת��Ϊʵ���¶�
		temp=~temp;
		temp=temp+1;//����ȡ�����¶�ֵȡ���ټ�1
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
 
  }
  else
  {			
  	LcdWriteCom(0x80);		//д��ַ 80��ʾ��ʼ��ַ
    LcdWriteData('+'); 		//��ʾ��
		tp=temp;//��Ϊ���ݴ�����С�������Խ��¶ȸ���һ�������ͱ���
		//����¶���������ô����ô�����Ĳ������������
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
  }
	datas[0] = temp / 10000;
  datas[1] = temp % 10000 / 1000;
  datas[2] = temp % 1000 / 100;
  datas[3] = temp % 100 / 10;
  datas[4] = temp % 10;
 
	LcdWriteCom(0x82);		  //д��ַ 80��ʾ��ʼ��ַ
  LcdWriteData('0'+datas[0]); //��λ 


  LcdWriteCom(0x83);		 //д��ַ 80��ʾ��ʼ��ַ
  LcdWriteData('0'+datas[1]); //ʮλ

	LcdWriteCom(0x84);		//д��ַ 80��ʾ��ʼ��ַ
  LcdWriteData('0'+datas[2]); //��λ 

	LcdWriteCom(0x85);		//д��ַ 80��ʾ��ʼ��ַ
  LcdWriteData('.'); 		//��ʾ ��.��

	LcdWriteCom(0x86);		 //д��ַ 80��ʾ��ʼ��ַ
  LcdWriteData('0'+datas[3]); //��ʾС����  

	LcdWriteCom(0x87);		 //д��ַ 80��ʾ��ʼ��ַ
  LcdWriteData('0'+datas[4]); //��ʾС����  

	LcdWriteCom(0x88);		//д��ַ 80��ʾ��ʼ��ַ
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
* ������         : Beep()
* ��������		   : ��������
* ����           : ��
* ���         	 : ��
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
void DigDisplay(void)
{
	unsigned char i;
	unsigned int j;
	for(i=0;i<8;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
		}
		GPIO_DIG=DisplayData[i];//���Ͷ���
		j=50;						 //ɨ����ʱ���趨
		while(j--);	
		GPIO_DIG=0x00;//����
	}
}
void AD_Main(void)
{

	  EA=0;
	  if(count==50)
	  {
	  	count=0; 
		temp = Read_AD_Data(0x94);		//   AIN0 ��λ��
	//	temp = Read_AD_Data(0xD4);		//   AIN1 ��������
	//	temp = Read_AD_Data(0xA4);		//   AIN2 ��������
	//	temp = Read_AD_Data(0xE4);		//   AIN3 �ⲿ����
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
	TMOD|= 0x10;   //���ö�ʱ������������ʽ1Ϊ��ʱ��

	//--��ʱ������ʼֵ��12MHZ�¶�ʱ1us--//  
	TH1 = 0xFF; 
	TL1 = 0xff;

	
	ET1 = 1; 	 //������ʱ��1�ж�
	EA = 1;
	TR1 = 1;	 //������ʱ��	
}
/*******************************************************************************
* �� �� ��       : Time1
* ��������		 : ��ʱ��1���жϺ���
* ��    ��       : ��
* ��    ��       : ��
*******************************************************************************/

void Time1(void) interrupt 3    //3 Ϊ��ʱ��1���жϺ�  1 ��ʱ��0���жϺ� 0 �ⲿ�ж�1 2 �ⲿ�ж�2  4 �����ж�
{
	TH1 = 0xFF;  //���¸���ֵ
	TL1 = 0xFf;
	timer1++; 
    countda++;
	
}
void DA_Main(void)
{  
		if(countda>100)							
		{  
			countda=0;
			if(DIR==1)					   //DIR�������ӻ��С
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
				
		if(timer1>1000)  //PWM����Ϊ100*1us
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
