/*******************************************************************************
* ʵ����			   : ������ˮ��ʵ��
* ʹ�õ�IO	     : P2
* ʵ��Ч��       : ������LED���ұ�������ƶ���������������ұ��ƶ�������ѭ����
*	ע��					 ��
*******************************************************************************/
ORG		00H
LJMP	INIT

ORG		30H
INIT:
MOV 	A ,#0FEH	;��A��ֵ

MAIN:
MOV 	R1,#007H	;���ƵĴ���
MOV 	R2,#007H	;���ƵĴ���
LIFT:
MOV 	P2 , A
RL 		A
ACALL 	DELAY		;������ʱ����
DJNZ 	R1,LIFT
RIGHT:
MOV 	P2,A
RR		A
ACALL 	DELAY
DJNZ 	R2,RIGHT
LJMP 	MAIN		;����������

DELAY:
MOV 	R5,#005H
DE1:
MOV 	R6,#0FFH
DE2:
MOV 	R7,#0FFH
DE3:
DJNZ 	R7,DE3
DJNZ 	R6,DE2
DJNZ 	R5,DE1
RET

END		