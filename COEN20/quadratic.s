//Dillon Kanai
//Feb 4, 2020
//quadratic.s

.syntax unified
.cpu cortex-m4
.text

//int32_t Discriminant(int32_t a, int32_t b, int32_t c)
	.global		Discriminant
	.thumb_func
	Discriminant: //return the value b^2 - 4ac
		MULS R1, R1, R1 //b^2
		LSL R0, R0, 2 //4a
		MLS R0, R0, R2, R1 //b^2 - 4ac
		BX LR //return R0

//int32_t Root1(int32_t a, int32_t b, int32_t c)
	.global 	Root1
	.thumb_func
	Root1: //return the value (-b + SquareRoot(Discriminant))/(2a)
		PUSH {R4, R5, LR}
		MOV R4, R0//a
		MOV R5, R1//b
		BL Discriminant //call discriminant and return value to R0
		BL SquareRoot //call SquareRoot and return value to R0
		NEG R2, R5
		ADDS R2, R2, R0 //-b + SR(Discriminant)
		LSL R4, R4, 1 //a*2
		SDIV R0, R2, R4 //(-b + SR(Discriminant))/2a
		POP {R4, R5, PC}
		
		
//int32_t Root2(int32_t a, int32_t b, int32_t c)
	.global 	Root2
	.thumb_func
	Root2: //return the value (-b - SquareRoot(Discriminant))/(2a)
		PUSH {R4, R5, LR}
		MOV R4, R0//a
		MOV R5, R1//b
		BL Discriminant //call discriminant and return value to R0
		BL SquareRoot //call SquareRoot and return value to R0
		NEG R2, R5
		SUBS R2, R2, R0 //-b - SR(Discriminant)
		LSL R4, R4, 1 //a*2
		SDIV R0, R2, R4 //(-b - SR(Discriminant))/2a
		POP {R4, R5, PC}
//int32_t Quadratic(int32_t x, int32_t a, int32_t b, int32_t c)
	.global 	Quadratic
	.thumb_func
	Quadratic: //return the value ax^2 + bx + c
		MULS R2, R2, R0 //bx
		MULS R0, R0, R0 //x^2
		MULS R1, R1, R0 //ax^2
		ADDS R0, R1, R2 //ax^2 + bx
		ADDS R0, R0, R3 //ax^2 + bx + c
		BX LR //return R0
	
	.end
	