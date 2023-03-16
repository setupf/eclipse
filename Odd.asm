	AREA PROG1, CODE, READONLY
		ENTRY	 
		LDR R5,= data1
		LDR R0,= 0x05
		MOV R7, #00
L1		LDR R4, [R5], #04
		MOVS R1, R4, LSR #01
		BCC L2
		ADD R7,R7, #01
L2		SUB R0, R0, #01
		BNE L1
STOP    B STOP

		AREA PROG1, DATA, READWRITE
data1	DCD 0xABCDEF12, 0xDCABFE43, 0xEEEEFFFF, 0xAAAABBBB, 0xCCCCCCC1                                                                                                                                                                                                                               
		END 
