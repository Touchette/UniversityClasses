/*  CIS 314 Computer Organization
 *  Problem 4-1
 *  Infer what happens in C code from IA32 Assembly
 *  Author: Touchette
 *  Completion Date: 2/12/2018
 *  --------------------------------------------------------
 *  The extremely long comments are more for my own ability
 *  to go back and study than anything else ... forgive me if they
 *  are too verbose
 */

#include <stdio.h>

// loop:
//         pushl %ebp            |  push the base pointer onto the stack
//         movl %esp, %ebp       |  move the stack pointer to the location of the base pointer
//         pushl %esi            |  push register %esi onto the stack
//         pushl %ebx            |  push register %ebx onto the stack
//         movl 8(%ebp), %esi    |  %esi = x (move "x" into %esi)
//         movl 12(%ebp), %ecx   |  %ecx = y (move "y" into %ecx)
//         movl $2, %edx         |  %edx = 2 = mask
//         movl $-1, %eax        |  %eax = -1 (%eax is the return value, result = -1)
// .L2:                          |
//         movl %esi, %ebx       |  %ebx = x, making a copy of x 
//         andl %edx, %ebx       |  %ebx = x & mask
//         xorl %ebx, %eax       |  result ^= (%ebx = x & mask)
//         sall %cl, %edx        |  shift (%edx = mask = 2) left by %cl, last byte of (%ecx = y)
//         cmpl $1, %edx         |  compare 1 to %edx = mask ...
//         jg   .L2              |  ... if greater than, do the for loop again 
//         popl %ebx             |  pop ebx off stack
//         popl %esi             |  pop esi off stack
//         popl %ebp             |  pop the base pointer off the stack
//         ret                   |  return

int loop(int x, int y) {
    int result = -1;

    for (int mask = 2; mask > 1; mask = (mask << y)) {
        result ^= (x & mask);
    }

    return result;
}

int main(int argc, char* argv[]) {
	// Pretty formatting for our main function to make it look like the
	// assignment PDF :)
    printf("loop(1, 5): %d\n", loop(1, 5));
    printf("loop(2, 4): %d\n", loop(2, 4));
    printf("loop(3, 3): %d\n", loop(3, 3));
    printf("loop(4, 2): %d\n", loop(4, 2));
    printf("loop(5, 1): %d\n", loop(5, 1));
}