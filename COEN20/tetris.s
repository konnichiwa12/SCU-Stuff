//Dillon Kanai
//February 18, 2020
//tetris.s
.syntax unified
.cpu cortex-m4

	.global GetBit
	.thumb_func
	//.set BITBANDING, 1
	.ifdef BITBANDING
	GetBit: //get a bit from the array pointed to by R0 and at position [R1][R2], use bit banding
		SUB R0, R0, 0x20000000
		LSLS.N R0, R0, 5
		ADD R0, R0, 0x22000000
		ADD R1, R2, R1, LSL 2
		LDR R0, [R0, R1, LSL 2]
		BX LR
	.else
	
	GetBit: //get a bit from the array pointed to by R0 and at position [R1][R2]
		LDRH R0, [R0]
		ADD R3, R2, R1, LSL 2 //get position [row][col]
		LSR R0, R0, R3 //left shift R0 by R3 times
		UBFX R0, R0 ,0, 1 //0 extend
		BX LR
		
	.endif
	
	.global PutBit
	.thumb_func
	.ifdef BITBANDING
	PutBit: //store a bit in the array pointed to by R0 and at position [R1][R2], use bit banding
		SUB R0, R0, 0x2000000
		LSLS.N R1, R1, 5
		ADD R2, R3, R2, LSL2
		ADD R1, R1, 0x22000000
		STR R0, [R1, R2, LSL 2]
		BX LR
		
	.else
	PutBit: //store a bit in the array pointed to by R0 and at position [R1][R2]
		PUSH {R4}
		ADD R2, R3, R2, LSL 2 //get position [row][col]
		MOV R3, 1 //get value of 1
		LSL R3, R2 //left shift value of 1 R2 times
		LSL R0, R0, R2 //left shift value of R0 R2 times
		LDR R4, [R1] //get copy of R1 address
		BIC R4, R4, R3 //Bit clear bit number R3 in R4
		ADD R4, R4, R0 //add R4 and R0 together
		STRH R4, [R1] //store newest value
		POP {R4}
		BX LR
	.endif
	
.end
