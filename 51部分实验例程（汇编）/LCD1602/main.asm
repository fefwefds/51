 	ORG 	000H
	LJMP 	INIT
	ORG 	0030H
	DB "P","e","c","h","i","n"," ","S","c","i","e","n","c","e" 	
	LCDE 	EQU 	P2.7
	RW 		EQU 	P2.5
	RS 		EQU 	P2.6
	GPIO_LCD EQU 	P0


INIT:
	ACALL 	LCD1602_Init ;��ʼ��1602
MAIN:
	MOV 	R7,#081H	 ;����дָ��
	ACALL 	LCD_WriteCom
	MOV 	A,#00H		;Ҫ��ȡ��һ��ĸ
	MOV 	DPTR,#0030H
	MOVC 	A,@A+DPTR	;��ȡ��P��
	MOV 	R7,A 		;����������һ������
	ACALL	LCD_WriteData
	MOV 	A,#01H
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	MOV 	A,#02H
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	MOV 	A,#03H
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	MOV 	A,#04H
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	MOV 	A,#05H
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	MOV 	A,#06H
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	MOV 	A,#07H
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	MOV 	A,#08H
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	MOV 	A,#09H
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	MOV 	A,#00AH
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	MOV 	A,#0BH
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	MOV 	A,#0CH
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	MOV 	A,#0DH
	MOVC 	A,@A+DPTR
	MOV 	R7,A
	ACALL 	LCD_WriteData
	AJMP 	$			;ԭ����ת
;*********************;
; 1602��ʼ������	  ��
;*********************;
LCD1602_Init: 	
	MOV 	R7,#038H	;���ݸ�LCD_WriteCom������ֵ����R7
	ACALL 	LCD_WriteCom;������ʾģʽ
	MOV 	R7,#00CH 	;������ʾ�������رա�
	ACALL 	LCD_WriteCom
	MOV 	R7,#006H 	;���õ�ַָ��д���1�������������ƶ�
	ACALL 	LCD_WriteCom
	MOV 	R7,#001H	;��ʾ����
	ACALL 	LCD_WriteCom
	MOV 	R7,#081H	;������ʼָ��
	ACALL 	LCD_WriteCom
	RET					;�Ӻ�������
;*********************;
; 1602д�������	  ��
;*********************;
LCD_WriteCom:		  ;��R7���մ���һ��8λ����
	CLR 	LCDE
	CLR 	RS
	CLR 	RW
	MOV 	GPIO_LCD,R7
	ACALL 	DELAY
	SETB 	LCDE
	ACALL 	DELAY
	CLR 	LCDE
	RET
;*********************;
; 1602д���ݳ���	  ��
;*********************;
LCD_WriteData:		  ;��R7���մ���һ��8λ����
	CLR 	LCDE
	SETB 	RS
	CLR 	RW
	MOV 	GPIO_LCD,R7
	ACALL 	DELAY
	SETB 	LCDE
	ACALL 	DELAY
	CLR 	LCDE
	RET
;*************;
; ��ʱ����	  ��
;*************;
DELAY:
	MOV 	R6,#0FFH
	DJNZ 	R6,$
	RET

END
	