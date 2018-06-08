/*  CIS 314 Computer Organization
 *  Problem 4-3
 *  Write inline IA32 for a do-while loop using C as basis
 *  Author: Touchette
 *  Completion Date: 2/12/2018
 *  --------------------------------------------------------
 *  The extremely long comments are more for my own ability
 *  to go back and study than anything else ... forgive me if they
 *  are too verbose
 */

#include <stdio.h>

// ----------------------------------------
// Given C code that does the do-while loop
// ---------------------------------------- 
// int sum(int from, int to) {
// 	int result = 0;
// 	do {
// 		result =+ from;
// 		++from;
// 	} while (from <= to);
// 	return result;
// }

int sum(int from, int to) {
	int result = 0;
	// Ensure that argument *from* is in %ecx,
	// argument *to* is in %edx, *result* is in %eax - do not modify.
	__asm__ ("movl %0, %%ecx # from in ecx;" :: "r" ( from ));
	__asm__ ("movl %0, %%edx # to in edx;" :: "r" ( to ));
	__asm__ ("movl %0, %%eax # result in eax;" :: "r" ( result ));

	// Your IA32 code goes below - comment each instruction... 
	__asm__ (".LOOP: # this sets the label of the following section");
    __asm__ ("addl %ecx, %eax # this adds the original value of from onto the result");
    __asm__ ("addl $1, %ecx # this adds 1 to from, effectively the next iteration;");
	__asm__ ("cmpl %edx, %ecx # compare 'from' and 'to'");
    __asm__ ("jle .LOOP # jump back, loop again if edx less than ecx ('to' less than 'from')");

	// Ensure that *result* is in %eax for return - do not modify.
	__asm__ ("movl %%eax, %0 # result in eax;" : "=r" ( result ));
	return result;
}

int main(int argc, char* argv[]) {
    // Pretty formatting for our main function to make it look like the
    // assignment PDF :)
    printf("sum(1, 6): %d\n", sum(1, 6));
    printf("sum(3, 5): %d\n", sum(3, 5));
    // My own check to see if it ACTUALLY worked... expected output of 6,
    // and it gave 6. 
    // printf("sum(1, 3): %d\n", sum(1, 3));
}
