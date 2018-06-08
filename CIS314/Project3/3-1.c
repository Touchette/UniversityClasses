/*  CIS 314 Computer Organization
 *  Problem 3-1
 *  Read user-inputted integers and store them in an IntArray struct
 *  Author: Touchette
 *  Completion Date: 2/4/2018
 *  --------------------------------------------------------
 *  The extremely long comments are more for my own ability
 *  to go back and study than anything else ... forgive me if they
 *  are too verbose
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFFER_SIZE 256

struct IntArray {
    // This is the same as the struct provided in lab, just renamed
    // to IntArray and the pointer renamed to *dataPtr
    int Length;
    int *dataPtr;
};


enum EXIT_CODES {
    // Used for exiting gracefully
    INVALID_POINTER = -1,
    BAD_DATA = -2
};


struct IntArray *mallocIntArray(int size) {
    if (size < 0) {
        printf("Invalid size.\n");
        exit(BAD_DATA);
    }
    struct IntArray *returnValue = NULL;                                // local variable to hold return value.
    returnValue = (struct IntArray *) malloc(sizeof(struct IntArray));  // allocate 1 struct on the heap.
    returnValue->Length = size;                                         // initiate size value.
    returnValue->dataPtr = (int *) malloc(sizeof(int) * size);          // allocate N*integers on the heap.
    for(int i=0; i<size; i++) {
        returnValue->dataPtr[i] = 0;                                    // initialize all memory to 0's.
    }
    return returnValue;                                                 // return the pointer to the struct on the heap.
}


void freeIntArray(struct IntArray **ptr) {
    if ((ptr != NULL) && ((*ptr) != NULL) && ((*ptr)->dataPtr != NULL)) {  // don't dereference a null pointer.
        for (int i=0; i<(*ptr)->Length; i++) {
            (*ptr)->dataPtr[i] = 0;                                        // un-init all memory to 0's.
        }
        free((*ptr)->dataPtr);                                             // de-allocate the array of integers.
        (*ptr)->dataPtr = 0;                                               // set the pointer to null.
        (*ptr)->Length = 0;                                                // set the size to 0.
        free((*ptr));                                                      // free the struct pointer.
        (*ptr) = NULL;                                                     // set the value of the passed in pointer to null.
    }
    else {
        fprintf(stderr, "Error in freeIntArray, bad pointer found.\n");
        exit(INVALID_POINTER);
    }
}


int getLength() {
    char buffer[BUFFER_SIZE];                                       // buffer the max amount of chars we can accept
    int* length;                                                    // the length we will get, "%d" requires int* type
    printf("Enter Length: ");                                       // set up the prompt to enter ints
    if (scanf("%d", length) != 1) {                                 // checking if the scanned in value is an int
        fprintf(stderr, "Input not recognised as an integer.\n");   // quit gracefully if not
        exit(BAD_DATA);                                              
    }

    int returned = *length;

    return returned;
}


void readIntArray(struct IntArray *array) {
    char buffer[BUFFER_SIZE];                                           // buffer the max amount of chars we can accept...
    for(int n=0; n<BUFFER_SIZE; n++) {                                  // and initialize this buffer to 0
       buffer[n] = 0;
    }

    int* givenInt;                                                      // initialize the int the user will give
    for (int i = 0; i < array->Length; i++) {
        printf("Enter int: ");                                          // set up the prompt to get the user's input "length" times
        if (scanf("%d", givenInt) != 1) {                               // check if user input is an integer
            fprintf(stderr, "Input not recognised as an integer.\n");   // exit gracefully if not
            exit(BAD_DATA);
        }
        array->dataPtr[i] = *givenInt;                                  // add the data to the array...
        array->Length = array->Length++;                                // and increment the length
    }
}


void swap(int *xp, int *yp) {
    // This swap function was written by Professor Wills on the
    // board in class as well as being offered in the book. I feel
    // that as such, I do not have to go into detail as to how it works.
    int t0 = *xp;
    int t1 = *yp;
    *xp = t1;
    *yp = t0;
}

void sortIntArray(struct IntArray *array) {
    // I took this from the first website I found when I googled C
    // bubblesort. It was made for C++, and took an actual int[] array
    // as input, but I modified it to work with our struct and in C.
    int i, j, n;
    n = array->Length;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (array->dataPtr[j] > array->dataPtr[j+1]) {
                swap(&array->dataPtr[j], &array->dataPtr[j+1]);
            }
        }
    }
}


void printIntArray(struct IntArray *array) {
    // Simply the print function that grabs data from the array
    // in the struct IntArray, formatted to look like the assignment.
    printf("[ ");
    for (int i = 0; i < (array->Length - 1); i++) {
        printf("%d, ", array->dataPtr[i]);
    }
    printf("%d ]\n", array->dataPtr[(array->Length-1)]);
}


int main(void) {
    // Pretty formatting that looks like the PDF :)
    int size = getLength();
    struct IntArray *array = mallocIntArray(size);
    readIntArray(array);
    sortIntArray(array);
    printIntArray(array);
    printf("\n");
    return EXIT_SUCCESS;
}
