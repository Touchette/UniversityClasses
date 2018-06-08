#include <stdio.h>

int even(unsigned int x) {
	/* need to mask out the even bits from x, a 32-bit word. similar 
	 * to masking all bits from a byte using the hex value 0xFF, so we just 
	 * need to find a mask that will isolate even-indexed bits **STARTING
	 * AT 0 FROM THE RIGHT**. if evens start at the right, we can't use 0xA, 
	 * instead have to use 0x5, which is the opposite. also, instead of 
	 * checking every 4 bits individually using 0x5, we can just mask the 
	 * full word and check it against 0 to see if any values are 1. if 
	 * there are, return 1, if not, return 0.
	 */
	unsigned int evenMask = 0x55555555;
	unsigned int zeroCheck = 0x0;

	return (x & evenMask != zeroCheck);
}

int main(int argc, char * argv[]) {
	// these are the sample inputs given in the assignment PDF, they
	// give the output 0, 1, 0, 1, 1, and 0 respectively
	printf("%x\n", even(0x0));
	printf("%x\n", even(0x1));
	printf("%x\n", even(0x2));
	printf("%x\n", even(0x3));
	printf("%x\n", even(0xFFFFFFFF));
	printf("%x\n", even(0xAAAAAAAA));
}