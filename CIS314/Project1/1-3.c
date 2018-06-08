#include <stdio.h>

unsigned int replace(unsigned int x, int i, unsigned int b) {
	/* so, for this line, we want to mask out the specific bits of "x" that 
	 * we want to replace. we have to shift the mask (0xff), which is one byte, 
	 * into the correct position for keeping the bits we want. we always want
	 * to shift it into a byte-long position, a multiple of 8. our input is
	 * a 32-bit word, so our shift is always going be 8 * i, where i ranges from
	 * zero to three. we can achieve this by taking "i" and shifting it to the 
	 * left by 3. since shifting to the left is the same operation as
	 * multiplication by 2^n, we always get 8 by shifting to the left by 3;
	 * this means we always get i * 8. then we simply shift our mask into the
	 * position. this means we can use the bitwise & operator with our original
	 * word to keep all the bytes except for the position we masked.
	 */
	x = (~(0xFF << (i << 3)) & x);
	// we're now doing the same operation to the byte we want to insert.
	// same operation as moving the mask.
	b = b << (i << 3);
	// this is the same method of combining that we used for part 1 of tihs
	// assignment, it uses the bitwise "or" operator.
	return x | b;
}

int main(int argc, char * argv[]) {
	// these are the sample inputs given in the assignment PDF, they
	// give the output 0x12AB5678 and 0x123456AB respectively
	printf("0x%08X\n", replace(0x12345678, 2, 0xAB));
	printf("0x%08X\n", replace(0x12345678, 0, 0XAB));
}