#include"ir.h"

unsigned char code CDIS1[13]={" Red Control "};
unsigned char code CDIS2[13]={" IR-CODE:--H "};
unsigned char IrValue[6];
unsigned char TimeCout;

/*******************************************************************************
* ������         : IrDisplayDatalay()
* ��������		   : LCD��ʾ��ȡ��������ֵ
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void IrDisplayDatalay()
{
		IrValue[5]=IrValue[2]>>4;	 	 	//��λ
		IrValue[6]=IrValue[2]&0x0f;		//��λ	
		if(IrValue[5]>9)
		{
			LcdWriteCom(0xc0+0x09);			//������ʾλ��
			LcdWriteData(0x37+IrValue[5]);	//����ֵת��Ϊ����ʾ��ASCII��
		}
		else
		{
			LcdWriteCom(0xc0+0x09);
			LcdWriteData(IrValue[5]+0x30);	//����ֵת��Ϊ����ʾ��ASCII��
		}	
		if(IrValue[6]>9)
		{
			LcdWriteCom(0xc0+0x0a);
			LcdWriteData(IrValue[6]+0x37);		//����ֵת��Ϊ����ʾ��ASCII��
		}
		else
		{
			LcdWriteCom(0xc0+0x0a);
			LcdWriteData(IrValue[6]+0x30);		//����ֵת��Ϊ����ʾ��ASCII��
		}
		LcdWriteData('H');
		
}
/*******************************************************************************
* ������         : IrInit()
* ��������		   : ��ʼ�������߽���
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void IrInit()
{
	IT0=1;//�½��ش���
	EX0=1;//���ж�0����
	EA=1;	//�����ж�

	IRIN=1;//��ʼ���˿�
}
/*******************************************************************************
* ������         : DelayMs()
* ��������		   : ��ʱ
* ����           : x
* ���         	 : ��
*******************************************************************************/

void DelayMs(unsigned int x)   //0.14ms��� 0us
{
 unsigned char i;
  while(x--)
 {
  for (i = 0; i<13; i++)
 {}
 }
}
/*******************************************************************************
* ������         : ReadIr()
* ��������		   : ��ȡ������ֵ���жϺ���
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void ReadIr() interrupt 0
{
	unsigned char j,k;
	unsigned int err;
	EA=0;
	TimeCout=0;					 
	DelayMs(70);

	if(IRIN==0)		//ȷ���Ƿ���Ľ��յ���ȷ���ź�
	{	 
		
		err=1000;				//1000*10us=10ms,����˵�����յ�������ź�
		while((IRIN==0)&&(err>0))	//�ȴ�ǰ��9ms�ĵ͵�ƽ��ȥ  		
		{												//������������Ϊ����ѭ���������һ������Ϊ�ٵ�ʱ������ѭ��
			
			DelayMs(1);
			err--;
		} 
		if(IRIN==1)			//��ȷ�ȵ�9ms�͵�ƽ
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //�ȴ�4.5ms����ʼ�ߵ�ƽ��ȥ
			{
				DelayMs(1);
				err--;
			}
			for(k=0;k<4;k++)		//����4������
			{				
				for(j=0;j<8;j++)	//����һ������
				{
					err=60;		
					while((IRIN==0)&&(err>0))//�ȴ��ź�ǰ���560us�͵�ƽ��ȥ
					while (!IRIN)
					{
						DelayMs(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //����ߵ�ƽ��ʱ�䳤�ȡ�
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
					IrValue[k]>>=1;	 //k��ʾ�ڼ�������
					if(TimeCout>=8)			//����ߵ�ƽ���ִ���460us����ô��1
					{
						IrValue[k]|=0x80;
					}
					TimeCout=0;		//����ʱ��Ҫ���¸�ֵ							
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