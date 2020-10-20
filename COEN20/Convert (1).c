/*Dillon Kanai
January 14, 2020
convert.cabsStarter code for Lab1 COEN20
*/

#include <stdint.h>
#include <math.h>

//converts the given array of bits to an unsignedned integer
//multiply each number of the bits array by 2 to the ith power (i refers to the place the number is in)
uint32_t Bits2Unsigned(int8_t bits[8]){
	int sum = 0;
	for (int i = 0; i < 8; i++){
		sum += pow(2, i)*bits[i];
	}
	return sum;
}

//converts the gucen array of bits to a signed int
//instead of converting using the signed integer algorithm, I simply subtracted 256 from all negative numbers in their positive forms, i left positive numbers alone
int32_t Bits2Signed(int8_t bits[8]){
	int sum = 0;
	sum = Bits2Unsigned(bits);
	if (sum > 127){
		return sum - 256;
	}
	return sum;
}

//add one to unsigned binary numbers
//i went through each binary number and turning each 1 into a 0. I keep going until I encounter a 0. I turn this 0 into a 1
void Increment(int8_t bits[8]){
	for (int i = 0; i < 8; i++){
		if (bits[i] == 1){
			bits[i] = 0;
		}
		else{
			bits[i] = 1;
			return;
		}
	}
	return;
}

//Turn a 32 bit int into an 8 bit binary number
//I used repeated division we learned in class: continue to divide by 2 and check the remainder. The remainder determines each bit from left to right.
void Unsigned2Bits(uint32_t n, int8_t bits[8]){
	for (int i = 0; i < 8; i++){
		if (n%2 == 1){
			bits[i] = 1;
		}
		else{
			bits[i] = 0;
		}
		n /= 2;
	}
	return;
}