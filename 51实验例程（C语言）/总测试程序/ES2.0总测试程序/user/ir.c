#include"ir.h"

unsigned char code CDIS1[13]={" Red Control "};
unsigned char code CDIS2[13]={" IR-CODE:--H "};
unsigned char IrValue[6];
unsigned char TimeCout;

/*******************************************************************************
* 函数名         : IrDisplayDatalay()
* 函数功能		   : LCD显示读取到红外线值
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void IrDisplayDatalay()
{
		IrValue[5]=IrValue[2]>>4;	 	 	//高位
		IrValue[6]=IrValue[2]&0x0f;		//低位	
		if(IrValue[5]>9)
		{
			LcdWriteCom(0xc0+0x09);			//设置显示位置
			LcdWriteData(0x37+IrValue[5]);	//将数值转换为该显示的ASCII码
		}
		else
		{
			LcdWriteCom(0xc0+0x09);
			LcdWriteData(IrValue[5]+0x30);	//将数值转换为该显示的ASCII码
		}	
		if(IrValue[6]>9)
		{
			LcdWriteCom(0xc0+0x0a);
			LcdWriteData(IrValue[6]+0x37);		//将数值转换为该显示的ASCII码
		}
		else
		{
			LcdWriteCom(0xc0+0x0a);
			LcdWriteData(IrValue[6]+0x30);		//将数值转换为该显示的ASCII码
		}
		LcdWriteData('H');
		
}
/*******************************************************************************
* 函数名         : IrInit()
* 函数功能		   : 初始化红外线接收
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void IrInit()
{
	IT0=1;//下降沿触发
	EX0=1;//打开中断0允许
	EA=1;	//打开总中断

	IRIN=1;//初始化端口
}
/*******************************************************************************
* 函数名         : DelayMs()
* 函数功能		   : 延时
* 输入           : x
* 输出         	 : 无
*******************************************************************************/

void DelayMs(unsigned int x)   //0.14ms误差 0us
{
 unsigned char i;
  while(x--)
 {
  for (i = 0; i<13; i++)
 {}
 }
}
/*******************************************************************************
* 函数名         : ReadIr()
* 函数功能		   : 读取红外数值的中断函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void ReadIr() interrupt 0
{
	unsigned char j,k;
	unsigned int err;
	EA=0;
	TimeCout=0;					 
	DelayMs(70);

	if(IRIN==0)		//确认是否真的接收到正确的信号
	{	 
		
		err=1000;				//1000*10us=10ms,超过说明接收到错误的信号
		while((IRIN==0)&&(err>0))	//等待前面9ms的低电平过去  		
		{												//当两个条件都为真是循环，如果有一个条件为假的时候跳出循环
			
			DelayMs(1);
			err--;
		} 
		if(IRIN==1)			//正确等到9ms低电平
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //等待4.5ms的起始高电平过去
			{
				DelayMs(1);
				err--;
			}
			for(k=0;k<4;k++)		//共有4组数据
			{				
				for(j=0;j<8;j++)	//接收一组数据
				{
					err=60;		
					while((IRIN==0)&&(err>0))//等待信号前面的560us低电平过去
					while (!IRIN)
					{
						DelayMs(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //计算高电平的时间长度。
					{
						DelayMs(1);
						TimeCout++;
						err--;
						if(TimeCout>30)
						{
							EA=1;
							return;
						}
					}
					IrValue[k]>>=1;	 //k表示第几组数据
					if(TimeCout>=8)			//如果高电平出现大于460us，那么是1
					{
						IrValue[k]|=0x80;
					}
					TimeCout=0;		//用完时间要重新赋值							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])
		{
			EA=1;
			return;
		}
	}
	EA=1;
	IrDisplayDatalay();			
}