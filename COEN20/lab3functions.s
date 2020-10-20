//Dillon Kanai
//January 28,2020
//lab3function.s

	.syntax unified
	.cpu cortex-m4
	.text
	
	.global UseLDRB
	.thumb_func
	//void UseLDRB(void *dst, void *src)
	UseLDRB: //Copy 1 byte of data 
		.rept 512 //repeat 512 times
		LDRB R2, [R1], 1 //Load a byte of data from the address within R1 to R2
		STRB R2, [R0], 1 //Store the byte of data in R2 into the address of R0
		.endr
		BX LR
	
	.global UseLDRH
	.thumb_func
	//void UseLDRH(void *dst, void *src)
	UseLDRH: //Copy 2 bytes of data 
		.rept 256 //repeat 256 times
		LDRH R2, [R1], 2 //Load 2 bytes of data from the address of R1 to R2
		STRH R2, [R0], 2 //Store 2 bytes of data in R2 to the address of R0
		.endr
		BX LR
	
	
	.global UseLDR
	.thumb_func
	//void UseLDR(void *dst, void *src)
	UseLDR: //Copy 4 bytes of data
		.rept 128 //repeat 128 times
		LDR R2, [R1], 4 //Load 4 bytes of data from address of R1 into R2
		STR R2, [R0], 4 //Store 4 bytes of data from R2 into address of R0
		.endr
		BX LR
	
	.global UseLDRD
	.thumb_func
	//void UseLDRD(void *dst, void *src)
	UseLDRD: //Copy 8 bytes of data
		.rept 64 //repeat 64 times
		LDRD R2, R3, [R1], 8 //Load 8 bytes of data from the address of R1 into R2 (least significant half) and R3(Most significant half)
		STRD R2, R3, [R0], 8 //Store 8 bytes of data from the addresses of R2(least significant half) and R3(most significant half) into the address of R0
		.endr
		BX LR
	
	.global UseLDM
	.thumb_func
	//void UseLDM(void *dst, void *src)
	UseLDM: //Store 32 bytes of data
		PUSH {R4-R9} //Push Register 4-9 into the stack bc we will be using them to handle the insane amount of input
		.rept 16 //repeat 16 times
		LDMIA R1!, {R2-R9} //Load 32 bytes of data from address of R1 into multiple registers (R2-R9) and update the address of R1
		STMIA R0!, {R2-R9} //Store 32 bytes of data from multiple registers (R2-R9) to the address of R0 and update the address of R0
		.endr
		POP {R4-R9} //pop R4-R9
		BX LR
	
	.end