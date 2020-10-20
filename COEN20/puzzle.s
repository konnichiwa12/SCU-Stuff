//Dillon Kanai
//February 11, 2020
//puzzle.s

.syntax unified
.cpu cortex-m4
.text

	.global CopyCell
	.thumb_func
	CopyCell: //increment through each pixel of a 60x60 tile and copy the 32 bit info from *src to *dst
			PUSH {R4}
			//R0 = dst
			//R1 = src
			MOV R2, 0//initialize row = 0
			//start loop
	Outer1:		
			CMP R2, 60
			BGE ExitOuter1 //if above condition false, break
			MOV R3, 0//initialize col = 0
	Inner1:		
			CMP R3, 60
			BGE ExitInner1 //if above condition false, break
			LDR R4, [R1, R3, LSL 2] //get value of src[col]
			STR R4, [R0, R3, LSL 2] //store value of src[col]
			ADDS R3, R3, 1 //col++
			B Inner1
	ExitInner1:
			ADDS R0, R0, 960 //move down to next row
			ADDS R1, R1, 960
			ADDS R2, R2, 1 //row++
			B Outer1
	ExitOuter1:		
			POP {R4}
			BX LR//return
			
			
			
	.global FillCell
	.thumb_func
	FillCell: //increment through a designated 60x60 pixel white tile and set each pixel to white
			//R0 = dst
			//R1 = pixel
			MOV R2, 0 //initialize row = 0
	Outer2:
			CMP R2, 60
			BGE ExitOuter2 //if above condition false, break
			MOV R3, 0 //initialize col = 0
	Inner2:
			CMP R3, 60
			BGE ExitInner2 //if above condition false, break
			STR R1, [R0, R3, LSL 2] //store value of pixel into dst[col]
			ADDS R3, R3, 1 //col++
			B Inner2
	ExitInner2:
			ADDS R0, R0, 960 //move to next row
			ADDS R2, R2, 1 //row++
			B Outer2
	ExitOuter2:
			BX LR //return 
			
.end
		
