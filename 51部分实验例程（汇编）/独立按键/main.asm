	ORG 	00H
	LJMP 	INIT
	ORG 	30H
;*************;
; 	������	  ��
;*************;
INIT:
	MOV 	A,#0FEH	

MAIN:
	MOV		P3,#0FFH
	MOV 	P2,A	
	JNB		P3.1,K1
	JNB 	P3.0,K2
	JNB 	P3.2,K3
	JNB 	P3.3,K4
	SJMP 	MAIN
;*************************;
; K1�������´������	  ��
;*************************;
K1:
	ACALL 	DELAY10MS	   ;��ʱ����
	JB 		P3.1,MAIN
	MOV 	A,00H
	MOV 	R2,#030H
KEY1_UP:
	ACALL 	DELAY10MS
	DJNZ	R2,KEY1_UP
	LJMP	MAIN
;*************************;
; K2�������´������	  ��
;*************************;
K2:
	ACALL	DELAY10MS
	JB		P3.0,MAIN
	MOV		A,#0FFH
	MOV 	R2,#030H
KEY2_UP:
	ACALL 	DELAY10MS
	DJNZ	R2,KEY2_UP
	LJMP	MAIN
;*************************;
; K3�������´������	  ��
;*************************;
K3:
	ACALL 	DELAY10MS
	JB 		P3.2,MAIN
	MOV 	R2,#030H
KEY3_UP:
	ACALL 	DELAY10MS
	DJNZ	R2,KEY3_UP
	CJNE 	A,00H,NEXT_K3	 ;���������00H����ôתȥ����Ƿ����FFH
NEXT3:	
	MOV 	A,#0FEH
	LJMP	MAIN
NEXT_K3:
	CJNE 	A,0FFH,RL3		 ;Ҳ������FFH��ôִ����������
	SJMP   	NEXT3			 ;�������FFH��ô���ظ�ֵFEH
RL3:
	RL		A
	LJMP	MAIN
;*************************;
; K4�������´������	  ��
;*************************;
K4:
	ACALL	DELAY10MS
	JB		P3.3,MAIN
	MOV 	R2,#030H
KEY4_UP:
	ACALL 	DELAY10MS
	DJNZ	R2,KEY4_UP
	CJNE 	A,000H,NEXT_K4
NEX4:
	MOV 	A,#0FEH
	LJMP	MAIN
NEXT_K4:
 	CJNE 	A,0FFH,RR4
	SJMP 	NEX4
RR4:
	RR		A
	LJMP	MAIN
;*************;
; ��ʱ����	  ��
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