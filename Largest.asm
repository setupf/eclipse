	AREA PROG1, CODE, READONLY
		ENTRY	 
		LDR R3, = data1
		LDR R4, = 0x05
		LDR R5, [R3], #04
		SUB R4, R4, #01
		MOV R7, #00
L1		LDR R1, [R3], #04
		CMP R1, R5
		BHS L2
		MOVS R1, R5
L2		SUBS R4, R4, #01
		BNE L1
STOP    B STOP

	AREA PROG1, DATA, READWRITE
data1	DCD 0x05, 0x03, 0x08, 0x04, 0x01                                                                                                                                                                                                                               
		END 
