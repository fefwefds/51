	ORG 	00H
	LJMP 	INIT
	ORG 	30H
	DB		03FH,006H,05BH,04FH,066H,06DH,07DH,007H,07FH,06FH
;*************;
; 	主程序	  ；
;*************;
INIT:
	CLR 	P2.2
	CLR 	P2.3
	CLR 	P2.4
	MOV 	R1,#00H
START:
	MOV		A,R1
	MOV 	DPTR,#30H
	MOVC 	A,@A+DPTR	
MAIN:
	MOV		P3,#0FFH 
	MOV 	P0,A	
	JNB		P3.1,K1
	JNB 	P3.0,K2
	JNB 	P3.2,K3
	JNB 	P3.3,K4
	SJMP 	MAIN
;*************************;
; K1按键按下处理程序	  ；
;*************************;
K1:
	ACALL 	DELAY10MS	   ;延时消抖
	JB 		P3.1,MAIN
	MOV 	R1,00H
	MOV 	R2,#030H
KEY1_UP:
	ACALL 	DELAY10MS
	DJNZ	R2,KEY1_UP		   ;按键延时
	LJMP	START
;*************************;
; K2按键按下处理程序	  ；
;*************************;
K2:
	ACALL	DELAY10MS
	JB		P3.0,MAIN
	MOV		R1,#09H
	MOV 	R2,#030H
KEY2_UP:
	ACALL 	DELAY10MS
	DJNZ	R2,KEY2_UP
	LJMP	START
;*************************;
; K3按键按下处理程序	  ；
;*************************;
K3:
	ACALL 	DELAY10MS
	JB 		P3.2,MAIN
	DEC 	R1
	MOV 	R2,#030H
KEY3_UP:
	ACALL 	DELAY10MS
	DJNZ	R2,KEY3_UP

	CJNE 	R1,#0FFH,KEY3
	MOV 	R1,#09H
KEY3:
	LJMP	START
;*************************;
; K4按键按下处理程序	  ；
;*************************;
K4:
	ACALL	DELAY10MS
	JB		P3.3,MAIN
	INC 	R1
	MOV 	R2,#030H
KEY4_UP:
	ACALL 	DELAY10MS
	DJNZ	R2,KEY4_UP
	 
	CJNE 	R1,#00AH,KEY4
	MOV  	R1,#00H
KEY4:
	LJMP	START
;*************;
; 延时程序	  ；
;*************;
DELAY10MS:
	MOV 	R6,#015H
DE1:
	MOV 	R7,#0F8H
DE2:
	DJNZ 	R7,DE2
	DJNZ 	R6,DE1
	RET

	END