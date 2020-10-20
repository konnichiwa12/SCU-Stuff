//Dillon Kanai
//March 3, 2020
//floating-point.s

.syntax unified
.cpu cortex-m4
.text

	.global Discriminant
	.thumb_func
	//float Discriminant(float a, float b, float c);
	Discriminant:
		VMUL.F32 S4, S1, S1 // b^2
		VMUL.F32 S5, S0, S2 //a*c
		VMOV S6, 4.0
		VMUL.F32 S5, S5, S6 //4ac
		VSUB.F32 S0, S4, S5 //b^2 - 4ac
		BX LR

	.global Quadratic
	.thumb_func
	//float Quadratic(float x, float a, float b, float c);
	Quadratic:
		VMUL.F32 S4, S0, S0 //x^2
		VMUL.F32 S1, S1, S4 //ax^2
		VMUL.F32 S2, S2, S0 //bx
		VADD.F32 S0, S1, S2 //ax^2 + bx
		VADD.F32 S0, S0, S3 //ax^2 + bx + c
		BX LR

	.global Root1
	.thumb_func
	//float Root1(float a, float b, float c);
	Root1:
		PUSH {R4, R5, LR}
		VMOV R4, S0//store variables
		VMOV R5, S1
		BL Discriminant //call Discriminant function
		VSQRT.F32 S4, S0 //Discriminant^.5
		VMOV S0, R4 //get saved variables
		VMOV S1, R5
		VNEG.F32 S3, S1 //-b
		VADD.F32 S3, S3, S4// -b + Dscriminant^.5
		VMOV S4, 2.0
		VMUL.F32 S1, S0, S4 //2a
		VDIV.F32 S0, S3, S1 //get (-b + Discriminant^.5)/(2a)
		POP {R4, R5, PC}

	.global Root2
	.thumb_func
	//float Root2(float a, float b, float c);
	Root2:
		PUSH {R4, R5, LR}
		VMOV R4, S0//store variables
		VMOV R5, S1
		BL Discriminant //call Discriminant function
		VSQRT.F32 S4, S0 //Discriminant^.5
		VMOV S0, R4 //get saved variables
		VMOV S1, R5
		VNEG.F32 S3, S1 //-b
		VSUB.F32 S3, S3, S4// -b - Dscriminant^.5
		VMOV S4, 2.0
		VMUL.F32 S1, S0, S4 //2a
		VDIV.F32 S0, S3, S1 //get (-b - Discriminant^.5)/(2a)
		POP {R4, R5, PC}
.end
