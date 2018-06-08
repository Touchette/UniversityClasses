/*  CIS 314 Computer Organization
 *  Problem 2-1
 *  Generate bitmask for specified n bits starting from right
 *  Author: Touchette
 *  Completion Date: 1/25/2018
 *  --------------------------------------------------------
 *  The extremely long comments are more for my own ability
 *  to go back study than anything else ... forgive me if they
 *  are too verbose
 */

#include <stdio.h>

unsigned int mask(int n) {
	/*  As per Professor Wills on Piazza, I'll use a long long data type here
	 *  instead of exploiting the "int" return type to get the correct answer.
	 *  This works because a long long is stored in 64 bits, so shifting to the
	 *  left by 32 is perfectly fine, thus we just need to perform two operations
	 *  on the mask to get it into the proper position.
	 */
	unsigned long long mask = 0xFFFFFFFF;

	return ~(mask << n);
}

// void binaryconversion(unsigned long long n) {
// 	// Here I have a function taken from StackOverflow that will
// 	// print a long long as binary; I used it to prove that I have 
//  // 64 bits of space to work with while checking my solution.
// 		while (n) {
// 		if (n & 1)
// 			printf("1");
// 		else
// 			printf("0");

// 		n >>=1;
// 	}
// 	printf("\n");
// }

int main(int argc, char* argv[]) {
	// Pretty formatting for our main function to make it look like the
	// assignment PDF :)
	// binaryconversion(0xABCDEF00);
	printf("mask(%i) : 0x%08X\n", 1, mask(1));
	printf("mask(%i) : 0x%08X\n", 2, mask(2));
	printf("mask(%i) : 0x%08X\n", 3, mask(3));
	printf("mask(%i) : 0x%08X\n", 5, mask(5));
	printf("mask(%i) : 0x%08X\n", 8, mask(8));
	printf("mask(%i): 0x%08X\n", 16, mask(16));
	printf("mask(%i): 0x%08X\n", 32, mask(32));

	return 0;
}