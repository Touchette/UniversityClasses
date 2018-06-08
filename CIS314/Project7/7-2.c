/*  CIS 314 Computer Organization
 *  Problem 7-2
 *  Optimize function via loop unrolling
 *  Author: Touchette
 *  Completion Date: 3/8/2018
 *  --------------------------------------------------------
 *  The extremely long comments are more for my own ability
 *  to go back and study than anything else ... forgive me if they
 *  are too verbose
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Size of the array, makes it easy to change and run
#define size 250000

void inner(float *u, float *v, int length, float *dest) {
    // Original function, makes "i" iterations through the arrays
    // which ends up being super expensive and time consuming.
	int i;
	float sum = 0.0f;
	for (i = 0; i < length; ++i) {
		sum += u[i] * v[i];
	}
	*dest = sum;
}

void inner2(float *u, float *v, int length, float *dest) {
    /* Using four parallel accumulators, we will sum up every
     * different array access for 4 indices at a time and then
     * at the end combine them all to give us the true result.
     * Furthermore, we finish any remaining elements with a second
     * loop that shouldn't run too many times. Note: running this code
     * on a Windows machine actually messed up the results and had me
     * debugging for over an hour. Not a great time.
     */

    // Four parallel accumulators.
    float sum0 = 0.0f;
    float sum1 = 0.0f;
    float sum2 = 0.0f;
    float sum3 = 0.0f;

    // Limit for the unrolling.
    int limit = length - 3;
    int i;

    // Unroll the loop 4 times.
    for (i = 0; i < limit; i+=4) {
        sum0 += (u[i] * v[i]);
        sum1 += (u[i+1] * v[i+1]);
        sum2 += (u[i+2] * v[i+2]);
        sum3 += (u[i+3] * v[i+3]);
    }

    for (; i < length; ++i) {
        sum0 += u[i] * v[i];
    }

    // Sum up unrolled multiplications.
    *dest = sum0 + sum1 + sum2 + sum3;
}

int main(int argc, char *argv[]) {
    // The arrays we will be using to multiply together, could use
    // one but I didn't want to risk it.
	float arrayA[size] = {[0 ... (size-1)] = 2.0 };
    float arrayB[size] = {[0 ... (size-1)] = 2.0 };

    // Destinations for our results to end up in.
	float dest1;
    float dest2;

    //-----------------------

    struct timeval start;
    gettimeofday(&start, NULL);

    // Run the function without unrolling it.
    printf("Inner: Without Unrolling:\n\n");
	inner(arrayA, arrayB, size, &dest1);

    struct timeval current;
    gettimeofday(&current, NULL);

    // Get time it took.
    long long elapsed = (current.tv_sec - start.tv_sec)*1000000LL + (current.tv_usec - start.tv_usec);
    printf("Time Elapsed:\t%f\n========================\n", elapsed/1000000.0);

    //-----------------------

    struct timeval start2;
    gettimeofday(&start2, NULL);

    // Run the optimized function with loop unrolling.
    printf("Inner2: With Unrolling:\n\n");
    inner2(arrayA, arrayB, size, &dest2);

    struct timeval current2;
    gettimeofday(&current2, NULL);

    // Get the time it took.
    long long elapsed2 = (current2.tv_sec - start2.tv_sec)*1000000LL + (current2.tv_usec - start2.tv_usec);
    printf("Time Elapsed:\t%f\n========================\n", elapsed2/1000000.0);

    //-----------------------

    // Show off the time difference.
    printf("Time Difference Due To Unrolling:\t%f\n", elapsed/1000000.0 - elapsed2/1000000.0);

    return 0;
}
