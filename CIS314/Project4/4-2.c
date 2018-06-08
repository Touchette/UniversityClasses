/*  CIS 314 Computer Organization
 *  Problem 4-2
 *  Optimize a transposing of an integer array via -O2 IA32 Assembly
 *  Author: Touchette
 *  Completion Date: 2/12/2018
 *  --------------------------------------------------------
 *  The extremely long comments are more for my own ability
 *  to go back and study than anything else ... forgive me if they
 *  are too verbose
 */

// .L3:
//    movl (%edx), %esi     | this is getting the pointers set up to the proper...
//    movl (%eax), %ecx     | ... array index, akin to *t0 and *t1 in the C code below
//    addl $4, %eax         | this is our offset for the bytesize of an integer
//    addl $40, %edx        | 40 because N = 10 in the example from the project PDF
//    movl %esi, -4(%eax)   | performing our swap...
//    movl %ecx, -40(%edx)  | ... continued
//    cmpl %ebx, %eax       | check conditional for the for loop
//    jne  .L3              | if they're not the same, do the loop again...

#include <stdio.h>

#define N 4
typedef int array_t[N][N];

void transpose(array_t a) {
	// Really complicated... took me forever to find out what was going on.
	// So, what happens in the optimization is that the compiler decides not
	// to do all the indexing into the arrays directly due to expensive operations.
	// Instead, it uses pointer arithmetic (because pointers are unsigned ints) to
	// keep track of all of the indices instead. It does this by first recording the
	// address of the very start of the array, a[0][0], and storing that address. 
	// Then it properly offsets itself into the correct position using the equation
	// where each entry is a certain amount of bytes offset from the start location.
	// The start is equal to (taken from Piazza, thanks John!):
	// = positions before current row + positions before desired column
	// = array[row2][column3] = 100 + (2 * 6 * 4) + (4 * 3), in a 5x6 array
	// Using this info, we know how to offset the pointer given "i", "N", and "j".
	// After offsetting the pointers and incrementing them to the proper positions,
	// we perform the swap (which is trivial at this point).
	int *ptr = &a[0][0];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < i; ++j) {
			int *t0 = ptr + (i * N + j);
			int *t1 = ptr + (j * N + i);
			int t2;
			t2 = *t0;
			*t0 = *t1;
			*t1 = t2;
		}
	}
}

void printArray(array_t a) {
	// Simple print function to print how the matrix looks, pretty much
	// ripped from 3-1 but works to print each row of the matrix and then
	// the newline for each row
	for (int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {
			printf("%d \t", a[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
    // Pretty formatting for the main function. Took me a long time to even
    // find out how to initialize the array, but it was in the project instructions
    // the entire time... woops
    int a[N][N] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
    printf("Array before transposing:\n");
    printArray(a);
    printf("\n");

    // Actually perform our transpose operation
    transpose(a);

    // Final print
    printf("Array after transposing:\n");
    printArray(a);
}