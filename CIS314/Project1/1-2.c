#include <stdio.h>

unsigned int combine (unsigned int x, unsigned int y) {
	/*  this mask will isolate the upper 8 bits of any unsigned int we 
	 *  "and" it with by usage of the bitwise & operator. it does
	 *  this by "anding" the upper 8 bits with F, which is all 1s in binary,
	 *  therefore we end up with 0s if the original int had 0s, and 1s if it had
	 *  1s.
	 */
	unsigned int upperMask = 0xFF000000;
	/*  this mask does the opposite of the other one, masking instead the 
	 *  lower 24 bits by the same method.
	 */
	unsigned int lowerMask = 0x00FFFFFF;

	// masking the first int's upper 8 bits with upperMask
	unsigned int xUpperBits = x & upperMask;
	// masking the second int's lower 24 bits with lowerMask
	unsigned int yLowerBits = y & lowerMask;

	/*  combine the two (now masked) ints via the bitwise "or" operator,
	 *  this works because we've masked all of the lower bits away from
	 *  x as well as all the upper bits away from y. this means that both
	 *  of them will combine flawlessly due to "x" having no lower bits in 
	 *  a "1" position and y having no upper bits in a "1" position.
	 */ 
	return xUpperBits | yLowerBits;
}

int main(int argc, char * argv[]) {
	// these are the sample inputs given in the assignment PDF, they
	// give the output 0x12CDEF00 and 0xAB345678 respectively
	printf("0x%08X\n", combine(0x12345678, 0xABCDEF00));
	printf("0x%08X\n", combine(0xABCDEF00, 0x12345678));
}