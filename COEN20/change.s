//Dillon kanai
//February 25, 2020
//change.s

.syntax unified
.cpu cortex-m4
.text

	.global Bills
	.thumb_func
	//void Bills(uint32_t dollars, BILLS *paper)
	Bills:
		LDR R2,=214748365 // 2^32/20
		SMMUL R2, R2, R0 //get number of 20s
		STR R2, [R1], 4 //store into struct
		LSL R3, R2, 2 //get R2*4
		ADD R2, R3, R2, LSL 4 //get R2*16 + R2*4
		SUB R0, R0, R2 //R0 - R2*20
		B Repeat
		
	.global Coins
	.thumb_func
	Coins:
		LDR R2,=171798692 // 2^32/25
		SMMUL R2, R2, R0 //get number of 20s
		STR R2, [R1], 4 //store into struct
		LSL R3, R2, 3 //get R2*8
		ADD R3, R3, R2, LSL 4 //get R2*16 + R2*4
		ADD R2, R2, R3 //get R2*16 + R2*4 + R2
		SUB R0, R0, R2 //R0 - R2*25
		B Repeat
		
	Repeat:
		LDR R2, = 429496730 //2^32/10
		SMMUL R2, R2, R0 //get number of 10s
		STR R2, [R1], 4 //store into struct
		LSL R3, R2, 3 //get R2*8
		ADD R2, R3, R2, LSL 1 //get R2*2 + R2*8
		SUB R0, R0, R2 //R0 - R2*10
		LDR R2, = 858993460 //2^32/5
		SMMUL R2, R2, R0 //get number of 5s
		STR R2, [R1], 4 //store into struct
		LSL R3, R2, 2 //get R2*4
		ADD R2, R3, R2 //get R2*4 + R2
		SUB R0, R0, R2 //R0 - R2*5
		STR R0, [R1] //store remaining amount
		BX LR
.end
