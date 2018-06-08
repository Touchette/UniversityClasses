/*  CIS 314 Computer Organization
 *  Problem 3-2
 *  Reverse Engineer IA32 Assembly Language into C code
 *  Author: Touchette
 *  Completion Date: 2/4/2018
 *  --------------------------------------------------------
 *  The extremely long comments are more for my own ability
 *  to go back and study than anything else ... forgive me if they
 *  are too verbose
 */

#include <stdio.h>

// x, y, and z are now at 8(%ebp), 12(%ebp), 16(%ebp) respectively when initializing this
int decode(int x, int y, int z) {
	int result, temp;   // setting up what will eventually be in %eax, %edx respectively
	temp = y;           // movl 12(%ebp), %edx ... move y into register %edx, call it temp
	temp -= z;          // subl 16(%ebp), %edx ... subtract z from value in %edx (temp = y)
	result = temp;      // movl %edx, %eax ... move temp into register %eax, which is result
	temp = x * result;  // imull 8(%ebp), %edx ... this puts a value in %edx, so x * result where %eax is implicit
	result <<= 31;      // sall $31, %eax ... self-explanatory shift to the left for value in %eax, result
	result >>= 31;      // sarl $31, %eax ... self-explanatory shift to the right for value in %eax, result
	result ^= temp;     // xorl %edx, %eax ... exclusive-or on the result with the temp variable which was multiplied by x

	return result;      // return the result value
}

int main(int argc, char* argv[]) {
	// Pretty formatting for our main function to make it look like the
	// assignment PDF :)
	printf("decode(1, 2, 4): %d\n", decode(1, 2, 4));
	printf("decode(-4, -8, -12): %d\n", decode(-4, -8, -12));
}