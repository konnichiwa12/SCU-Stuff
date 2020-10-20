//Dillon Kanai
//January 21,2020
//functions.s

.syntax 	unified
.cpu		cortex-m4
.text

//int32_t Add(int32_t a, int32_t b)
	.global		Add
	.thumb_func
	
	Add:
		//return a+b
		ADD R0, R0, R1 //R0 <- a + b
		BX LR //return R0


//int 32_t Less1(int32_t a)
	.global		Less1
	.thumb_func
	
	Less1:
		//return a - 1
		SUB R0, R0, 1 //R0 <- a - 1
		BX LR //return R0


//int 32_t Square2x(int32_t x)
	.global Square2x
	.thumb_func
	
	Square2x:
		//return Square(x+x)
		PUSH {LR} //Push link register onto the stack
		ADD R0, R0, R0 //R0 <- x + x
		BL Square //Get x * x
		POP {PC} //return R0


//int 32_t Last(int32_t x)
	.global		Last
	.thumb_func
	
	Last:
		//return x + SquareRoot(x)
		PUSH {R4, LR} //Push R4 and link register onto the stack
		MOV R4, R0 // Preserve x in R4
		BL SquareRoot //find square root of x
		ADD R0, R0, R4 // R0 <- SquareRoot(x) + x
		POP {R4, PC} //return R0

.end