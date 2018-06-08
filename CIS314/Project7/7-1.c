/*  CIS 314 Computer Organization
 *  Problem 7-1
 *  Optimize function via removing unnecessary func calls, etc.
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

#define N 1000

typedef int array_t[N][N];

int dim() {
    // Given function to return dimension of array
	return N;
}

void f(array_t a, int x, int y) {
    // Given unoptimized code that does unnecessary
    // multiplications and function calls within loops
    for (int i = 0; i < dim(); ++i) {
        for (int j = 0; j < dim(); ++j) {
            a[i][j] = i * x * y + j; 
        }
    }
}

void g(array_t a, int x, int y) {
    // Bringing function call outside of loop statement
	int size = dim();
    // Bringing multiplication of constants outside of loop body
    int temp = x * y;
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Here we have the multiplication 
            a[i][j] = (i * temp) + j; 
        }
	}
}


int main(int argc, char* argv[]) {
    // Building array of size N for both functions, f and g.
    // this uses gcc syntax to fill an array {[0 ... (size-1)] = 1} 
    // will make an integer array initialized with 1s of size "size".
    int fa[N][N] = { {[0 ... (N-1)] = 1}, {[0 ... (N-1)] = 2}, {[0 ... (N-1)] = 3}, {[0 ... (N-1)] = 4} };
    int ga[N][N] = { {[0 ... (N-1)] = 5}, {[0 ... (N-1)] = 6}, {[0 ... (N-1)] = 7}, {[0 ... (N-1)] = 8} };

    struct timeval startf;
    gettimeofday(&startf, NULL);

    // Run the original, unoptimized function
    f(fa, 100, 200);

    struct timeval currentf;
    gettimeofday(&currentf, NULL);

    long long elapsedf = (currentf.tv_sec - startf.tv_sec)*1000000LL + (currentf.tv_usec - startf.tv_usec);
    // Get the time it took to run it
    printf("f():\t%f\n", elapsedf/1000000.0);

    //------------------------

    struct timeval startg;
    gettimeofday(&startg, NULL);

    // Run the optimized function
    g(ga, 100, 200);

    struct timeval currentg;
    gettimeofday(&currentg, NULL);
    long long elapsedg = (currentg.tv_sec - startg.tv_sec)*1000000LL + (currentg.tv_usec - startg.tv_usec);
    // Get the time it took to run it
    printf("g():\t%f\n", elapsedg/1000000.0);

    return 0;
}
