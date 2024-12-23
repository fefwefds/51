#include"lcd12864.h"

/*******************************************************************************
* 函 数 名         : LCD12864_Delay1ms
* 函数功能		   : 延时1MS
* 输    入         : c
* 输    出         : 无
*******************************************************************************/

void LCD12864_Delay1ms(uint c)
{
    uchar a,b;
	for(; c>0; c--)
	{
	    for(b=199; b>0; b--)
		{
	        for(a=1; a>0; a--);
		}
	}
}

/*******************************************************************************
* 函 数 名         : LCD12864_Busy
* 函数功能		   : 检测LCD是否忙
* 输    入         : 无
* 输    出         : 1或0（1表示不忙，0表示忙）
*******************************************************************************/

uchar LCD12864_Busy(void)
{
	uchar i = 0;

	LCD12864_RS = 0;   	//选择命令
	LCD12864_RW = 1;	//选择读取

	LCD12864_EN = 1;
	LCD12864_Delay1ms(1);

	while((LCD12864_DATAPORT & 0x80) == 0x80)	//检测读取到的值
	{
		i++;
		if(i > 100)
		{
			LCD12864_EN = 0;
			return 0;	   //超过等待时间返回0表示失败
		}
	}

	LCD12864_EN = 0;

	return 1;
}

/*******************************************************************************
* 函 数 名         : LCD12864_WriteCmd
* 函数功能		   : 写命令
* 输    入         : cmd
* 输    出         : 无
*******************************************************************************/

void LCD12864_WriteCmd(uchar cmd)
{
	uchar i;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		LCD12864_Delay1ms(1);
		i++;
		if( i>100)
		{
			return;	   //超过等待退出
		}	
	}
	
	LCD12864_RS = 0;     //选择命令
	LCD12864_RW = 0;     //选择写入
	LCD12864_EN = 0;     //初始化使能端

	LCD12864_DATAPORT = cmd;   //放置数据

	LCD12864_EN = 1;		   //写时序
	LCD12864_Delay1ms(1);
	LCD12864_EN = 0;    					
}

/*******************************************************************************
* 函 数 名         : LCD12864_WriteData
* 函数功能		   : 写数据
* 输    入         : dat
* 输    出         : 无
*******************************************************************************/

void LCD12864_WriteData(uchar dat)
{
	uchar i;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		LCD12864_Delay1ms(1);
		i++;
		if( i>100)
		{
			return;	   //超过等待退出
		}	
	}

	LCD12864_RS = 1;     //选择数据
	LCD12864_RW = 0;     //选择写入
	LCD12864_EN = 0;     //初始化使能端

	LCD12864_DATAPORT = dat;   //放置数据

	LCD12864_EN = 1;		   //写时序
	LCD12864_Delay1ms(1);
	LCD12864_EN = 0;    								
}

/*******************************************************************************
* 函 数 名         : LCD12864_ReadData
* 函数功能		   : 读取数据
* 输    入         : 无
* 输    出         : 读取到的8位数据
*******************************************************************************/
#ifdef LCD12864_PICTURE

uchar LCD12864_ReadData(void)
{
	uchar i, readValue;

	i = 0;
	while( LCD12864_Busy() == 0)
	{
		LCD12864_Delay1ms(1);
		i++;
		if( i>100)
		{
			return 0;	   //超过等待退出
		}	
	}

	LCD12864_RS = 1;       //选择命令
	LCD12864_RW = 1;
	LCD12864_EN = 0;
	LCD12864_Delay1ms(1);  //等待

	LCD12864_EN = 1;
	LCD12864_Delay1ms(1);
	readValue = LCD12864_DATAPORT;
	LCD12864_EN = 0;

	return readValue;
}

#endif

/*******************************************************************************
* 函 数 名         : LCD12864_Init
* 函数功能		   : 初始化LCD12864
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void LCD12864_Init()
{
	LCD12864_PSB = 1;	  //选择并行输入
	LCD12864_RST = 1;	  //复位

	LCD12864_WriteCmd(0x30);  //选择基本指令操作
	LCD12864_WriteCmd(0x0c);  //显示开，关光标
	LCD12864_WriteCmd(0x01);  //清除LCD12864的显示内容
}

/*******************************************************************************
* 函 数 名         : LCD12864_ClearScreen
* 函数功能		   : 在画图模式下，LCD12864的01H命令不能清屏，所以要自己写一个清
*                  * 屏函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
#ifdef LCD12864_PICTURE

void LCD12864_ClearScreen(void)
{
	uchar i,j;

	LCD12864_WriteCmd(0x34);	  //开启拓展指令集

	for(i=0;i<32;i++)			  //因为LCD有纵坐标32格所以写三十二次
	{
		LCD12864_WriteCmd(0x80+i);		  //先写入纵坐标Y的值
		LCD12864_WriteCmd(0x80);		  //再写入横坐标X的值
		for(j=0;j<32;j++)		  //横坐标有16位，每位写入两个字节的的数据，也
		{						  //就写入32次以为当写入两个字节之后横坐标会自
			LCD12864_WriteData(0x00);	  //动加1，所以就不用再次写入地址了。
		}
	}

	LCD12864_WriteCmd(0x36);	 //0x36扩展指令里面打开绘图显示
	LCD12864_WriteCmd(0x30);	 //恢复基本指令集
}

#endif
/*******************************************************************************
* 函 数 名         : LCD12864_SetWindow
* 函数功能		   : 设置在基本指令模式下设置显示坐标。注意：x是设置行，y是设置列
* 输    入         : x, y
* 输    出         : 无
*******************************************************************************/

void LCD12864_SetWindow(uchar x, uchar y)
{
	uchar pos;

	if(x == 0)	   // 第一行的地址是80H
	{
		x = 0x80;
	}
		
	else if(x == 1)  //第二行的地址是90H
	{
		x = 0x90;	
	}
	
	else if(x == 2)  //第三行的地址是88H
	{
		x = 0x88;
	}
	
	else if(x == 3)
	{
		x = 0x98;
	}
	
	pos = x + y;
	LCD12864_WriteCmd(pos);
}

/*******************************************************************************
* 函 数 名         : LCD12864_ClearScreen
* 函数功能		   : 在画图模式下，LCD12864的01H命令不能清屏，所以要自己写一个清
*                  * 屏函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
#ifdef LCD12864_PICTURE

void LCD12864_DrowPic(uchar *a)	   
{

	unsigned char i,j;

	LCD12864_ClearScreen();

	LCD12864_WriteCmd(0x34);      //开启扩展指令集，并关闭画图显示。
	for(i=0;i<32;i++)			  //因为LCD有纵坐标32格所以写三十二次
	{
		
		LCD12864_WriteCmd(0x80+i);		  //先写入纵坐标Y的值
		LCD12864_WriteCmd(0x80);		  //再写入横坐标X的值
		for(j=0; j<16; j++)		  //横坐标有16位，每位写入两个字节的的数据，也
		{						  //就写入32次以为当写入两个字节之后横坐标会自
			LCD12864_WriteData(*a); 	      //动加1，所以就不用再次写入地址了。
			a++;
		}
	}  
	for(i=0; i<32; i++)			  //因为LCD有纵坐标32格所以写三十二次
	{
		
		LCD12864_WriteCmd(0x80+i);		  //先写入纵坐标Y的值
		LCD12864_WriteCmd(0x88);		  //再写入横坐标X的值
		for(j=0; j<16; j++)		  //横坐标有16位，每位写入两个字节的的数据，也
		{						  //就写入32次以为当写入两个字节之后横坐标会自
			LCD12864_WriteData(*a); 	      //动加1，所以就不用再次写入地址了。
			a++;		}
	}	

	LCD12864_WriteCmd(0x36);	   //开显示
	LCD12864_WriteCmd(0x30);  	   //转回基本指令集
}

/*******************************************************************************
* 函 数 名         : LCD12864_DrowPoint
* 函数功能		   : 在一定的坐标点亮一个点，可以用于画线条
* 输    入         : x, y
* 输    出         : 无
*******************************************************************************/

void LCD12864_DrowPoint(uchar x, uchar y)
{
	uint bt = 0, readValue = 0;
	uchar x_adr, y_adr, h_bit, l_bit;

	//--Y轴最大一共64，但是12864分为上半屏和下半屏，超过32就是下半屏了，--//
	//--地址得又从零开始了。所以对32求余数，得到Y轴的坐标，然后加上80H的基地址--//
	y_adr = 0x80 + y % 32;		//计算Y轴的地址	
	
	//--当Y大于31时是下半屏，X（水平位置的地址）是从88H开始的，而且它是16位一--//
	//--个地址，所以对16求模。而上半屏的地址是从80H开始的--// 
	if(y>31)
	{
		x_adr = 0x88 + x / 16;	//计算X轴的地址
	}
	
	else
	{
		x_adr = 0x80 + x / 16;
	}
	
	//--求出X（水平位置），点亮的点是在16位数据里面的哪一个位--//
	//--所以对这个数求余数--//
	bt = 0x8000 >> (x % 16);

	LCD12864_WriteCmd(0x34);	  //进入拓展指令集

	LCD12864_WriteCmd(y_adr);	  //读取数据的时候要先写入所取数据的地址
	LCD12864_WriteCmd(x_adr);

	LCD12864_ReadData();		  //读取的第一个字节不要，
	readValue = LCD12864_ReadData();	  //从第二个字节开始接收。
	readValue <<= 8;
	readValue |= LCD12864_ReadData();
	bt = bt | readValue;
	h_bit = bt >> 8;
	l_bit = bt;

	LCD12864_WriteCmd(y_adr);	   //写入点的时候，从新写入地址，因为地址已经改变。
	LCD12864_WriteCmd(x_adr);

	LCD12864_WriteData(h_bit);
	LCD12864_WriteData(l_bit);

	LCD12864_WriteCmd(0x36);	   //开显示
	LCD12864_WriteCmd(0x30);	   //关闭绘图指令集	
}
#endif
