/*  CIS 314 Computer Organization
 *  Problem 2-2
 *  Extract certain byte from signed integer x
 *  Author: Touchette
 *  Completion Date: 1/25/2018
 *  --------------------------------------------------------
 *  The extremely long comments are more for my own ability
 *  to go back study than anything else ... forgive me if they
 *  are too verbose
 */

#include <stdio.h>

unsigned int extract(unsigned int x, int i) {
	// Explicitly typecast our parameter into a signed integer instead of
	// an unsigned one
	signed int a = *((signed int *) &x);
	// Create the mask
	signed int bytemask = 0xFF;
	// Shift the bytemask into the correct position as given by our
	// second parameter, i
	bytemask = bytemask << (i << 3);

	// Mask out the important bits (aka the ones we want to extract) from
	// "x" (now a) by using & with the bytemask
	a = (a & bytemask);
	/*  Since we need to use an arithmetic shift to the right, keeping the
	 *  leftmost byte and padding with it, we shift our newly acquired byte
	 *  all the way to the left by shifting it by the full word length (31)
	 *  MINUS the amount we shifted the mask into position, ie; the remainder
	 *  of the bits to reach the far left.
	 */
	a = (a << (31 - i << 3));
	/*  Move the byte back to the end, because the byte is always at the leftmost
	 *  position due to the previous operation. Thus we can explicitly move it by
	 *  24 bits to get it to the rightmost byte position.
	 */	
	a = (a >> (24));

	return a;
}

int main(int argc, char* argv[]) {
	// Pretty formatting for our main function to make it look like the
	// assignment PDF :) 
	printf("extract(0x%08X, %i) : %08X\n", 0x12345678, 0, extract(0x12345678, 0));
	printf("extract(0x%08X, %i) : %08X\n", 0xABCDEF00, 2, extract(0xABCDEF00, 2));

	return 0;
}