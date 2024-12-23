#include"ds1302.h"


//DS1302写入和读取时分秒的地址命令
unsigned char READ_RTC_ADDR[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d}; //秒分时日月周年 最低位读写位};
unsigned char WRITE_RTC_ADDR[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};
//DS1302时钟初始化03-1-1-12-0-0。存储顺序是秒分时日月年,存储格式是用BCD码
unsigned char TIME[6]={0,0,0x12,0x01,0x01,0x03};

/*******************************************************************************
* 函数名         : Ds1302WriteByte
* 函数功能		   : 向DS1302写入一个字节
* 输入           : dat
* 输出         	 : 无
*******************************************************************************/

void Ds1302WriteByte(unsigned char dat)
{
	unsigned char n;
	for(n=8;n>0;n--)
	{
		SCLK=0;
		_nop_();
		DSIO=dat&0x01;	//先发送最低位
		dat>>=1;				//右移一位
		_nop_();
		SCLK=1;//上升沿的时候输入
		_nop_();
	}
}

/*******************************************************************************
* 函数名         : Ds1302ReadByte(
* 函数功能		   : 读取DS1302一个字节
* 输入           : 无
* 输出         	 : dat
*******************************************************************************/

unsigned char Ds1302ReadByte()
{
	unsigned char n,dat,dat1;
	for(n=8;n>0;n--)
	{
		SCLK=0;
		_nop_();
		dat1=DSIO;
		dat=(dat>>1)|(dat1<<7);
		SCLK=1;
		_nop_();
	}
	return dat;
}
/*******************************************************************************
* 函数名         : Ds1302Write
* 函数功能		   : 向DS1302命令（地址+数据）
* 输入           : addr,dat
* 输出         	 : 无
*******************************************************************************/

void Ds1302Write(unsigned char addr,unsigned dat)
{
	RST=0;
	_nop_();
	SCLK=0;
	_nop_();
	_nop_();
	RST=1;
	_nop_();
	Ds1302WriteByte(addr);
	Ds1302WriteByte(dat);
	RST=0;	
}
/*******************************************************************************
* 函数名         : Ds1302Read
* 函数功能		   : 读取一个地址的数据
* 输入           : addr
* 输出         	 : dat
*******************************************************************************/

unsigned char Ds1302Read(unsigned char addr)
{
	unsigned char dat;
	RST=0;
	_nop_();
	SCLK=0;
	_nop_();
	_nop_();
	RST=1;
	_nop_();
	Ds1302WriteByte(addr);
	dat=Ds1302ReadByte();
	
	RST=0;		 //以下为1302复位的稳定时间，必须的
	_nop_();
	SCLK=0;
	_nop_();
	SCLK=1;
	_nop_();
	DSIO=0;
	_nop_();
	DSIO=1;
	_nop_();
	return dat;
}
/*******************************************************************************
* 函数名         : Ds1302Init
* 函数功能		   : 初始化DS1302.
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void Ds1302Init()
{

	unsigned char n;
	Ds1302Write(0x8E,0X00);		 //禁止写保护，就是关闭写保护功能

	for(n=0;n<7;n++)
	{
		Ds1302Write(WRITE_RTC_ADDR[n],TIME[n]);	
	}
	Ds1302Write(0x8E,0x80);		 //打开写保护功能
}
void Ds1302ReadTime()
{
	unsigned char n;
	for(n=0;n<7;n++)
	{
		TIME[n]=Ds1302Read(READ_RTC_ADDR[n]);
	}
		
}


