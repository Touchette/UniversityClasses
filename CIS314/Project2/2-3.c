/*  CIS 314 Computer Organization
 *  Problem 2-3
 *  Returning if float x is greater than or equal to float y
 *  Author: Touchette
 *  Completion Date: 1/25/2018
 *  --------------------------------------------------------
 *  The extremely long comments are more for my own ability
 *  to go back study than anything else ... forgive me if they
 *  are too verbose
 */

#include <stdio.h>

int ge(float x, float y) {
	unsigned ux = *((unsigned *) &x);
	unsigned uy = *((unsigned *) &y);
	unsigned sx = ux >> 31; // extract sign bit of ux
	unsigned sy = uy >> 31; // extract sign bit of uy
	ux <<= 1; // drop sign bit of ux
	uy <<= 1; // drop sign bit of uy

	/*  Since this is a single return statement that got quite long, I thought I would break it down
	 *  statement by statement:
	 *  Statement One:
	 *  	((ux == 0) & (uy == 0)) | ...
	 *  	This statement is quite simple in its implementation, it's just checking if ux and uy 
	 *  	are both equal to 0. If they are, then they're equal, so it will return 1 (True).
	 *  Statement Two:
	 *  	((sx ^ sy) & sy) | ...
	 *  	This statement is also quite simple in concept, we're simply checking for sign differences.
	 *  	We use exclusive or (^) to check if the signs are different, then with logical and (&) it 
	 *  	with sy. If the two vary, and y is the negative one, then x >=y.
	 *  Statement Three:
	 *  	((sx ^ sy ^ 1) & ((ux == uy) | (sy ^(ux > uy))));
	 *  	Clearly the most complicated of the three, this statement is similar in logic to the previous
	 *  	statement. (sx ^ sy ^ 1) is equivalent to the xnor operator, but as there is no symbol for it,
	 *  	we do it this way. This is the opposite of doing sx ^ sy, as in, we are now checking if they
	 *		have the SAME sign. So if they have the same sign, AND they are equal, OR x is bigger.
	 *		To expand out the XOR statement, we can think of it as BOTH are negative, thus we want x to be
	 *		NOT bigger (aka less negative). This is special, we want x to be NOT bigger, not simply smaller,
	 *		so we can catch the >= case for negative numbers. This is why we need the extra ux == uy for
	 *		this statement to catch positive number cases as well.
	 */
	return ((ux == 0) & (uy == 0)) | ((sx ^ sy) & sy) | ((sx ^ sy ^ 1) & ((ux == uy) | (sy ^ (ux > uy))));
}

int main(int argc, char* argv[]) {
	// Pretty formatting for our main function to make it look like the
	// assignment PDF :) 
	printf("ge(%.1ff, %.1ff) : %i\n", 0.0f, 0.0f, ge(0.0f, 0.0f));
	printf("ge(%.1ff, %.1ff): %i\n", -0.0f, 0.0f, ge(-0.0f, 0.0f));
	printf("ge(%.1ff, %.1ff): %i\n", -1.0f, 0.0f, ge(-1.0f, 0.0f));
	printf("ge(%.1ff, %.1ff) : %i\n", 0.0f, 1.0f, ge(0.0f, 1.0f));
	printf("ge(%.1ff, %.1ff) : %i\n", 1.0f, 0.0f, ge(1.0f, 0.0f));
	printf("ge(%.1ff, %.1ff): %i\n", 0.0f, -1.0f, ge(0.0f, -1.0f));

	return 0;
}
