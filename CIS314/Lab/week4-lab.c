#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void swap(int *xp, int *yp) {
    int t0 = *xp;
    int t1 = *yp;
    *xp = t1;
    *yp = t0;
}

struct BinArray {
    int Length;
    int *Data;
};

enum EXIT_CODES {
    INVALID_POINTER = -1,
    BAD_DATA = -2
};

int arith(int x, int y, int z) {
                          // movl 8(%ebp), %ecx          | ecx = x
    int t1 = x + y;       // movl 12(%ebp), %edx         | edx = y
    int t2 = z + t1;      // leal  (%edx, %edx, 2), %eas | eax = y*3
    int t3 = x + 4;       // sall  $4, %eax              | eax *= 16 (t4)
    int t5 = t3 + t4;     // leal  4(%ecx, %eax), %eax   | eax = t4 + x + 4 (t5)
    int rval = t2 * t5;   // addl  %ecx, %edx            | edx = x + y (t1)
                          // addl  16(%ebp), %edx        | edx += z (t2)
    return rval;          // imull %edx, %eax            | eax = t2 * t5 (rval)
}

unsigned int ParseBinary(char *data, int length) {
    // D(Rb, Ri, S):
    // Mem[Reg[Rb] + S * Reg[Ri] + D]
    // S can only be 1, 2, 4, 8

    // For example:
    //     Mem[a + 4 * i]
    //  a-> [....|....|....|....|....]
    //  size of int == 4
    int position = 0;  // variable to keep track of current index.
    char item = 0;  // value at the current index.
    unsigned int returnValue = 0;  // final value to return.
    int negative = 0;  // flag for signed values.

    if (data == NULL) {
        fprintf(stderr, "Invalid Data Pointer.\n");
        exit(INVALID_POINTER);
    }
    if (data[position] == '-') {  // check for otional signed value, do not increment.
        negative = 1;  // set the flag and increment the index
        position++;
    }
    if (data[position++] != '0') {
        fprintf(stderr, "Bad Start Character: %c\n Must be -?0(b|B)XXXXXXXX\n", item);
        exit(BAD_DATA);
    }
    item = data[position++];  // save the item and increment the pointer.
    if ((item != 'b') && (item != 'B')) {  // test for valid data.
        fprintf(stderr, "Bad Leading Character: %c\nMust be -?0(b|B)XXXXXXXX\n", item);
        exit(BAD_DATA);
    }
    // all leading characters have been consumed, XX...XX can now be parsed, X = (0|1)
    for(; position < length; position++) {  // loop through all of the characters.

        item = data[position];  // get the current char in the array.

        switch(item) {
            case '0':
                returnValue = returnValue << 1;  // shift answer left,
                break;                           // augment by 0.
            case '1':
                returnValue = returnValue << 1;  // shift answer left,
                returnValue = returnValue | 1;   // augment by 1.
                break;
            case '\r':  // return newline, and end of line, do nothing.
            case '\n':
            case 0:
                break;
            default:  // all other input is an error.
                fprintf(stderr, "Error/Invalid Data input:%d\n", item);
                exit(BAD_DATA);
                break;
        }
    }
    if (negative) {  // take the 2's compliment of the binary number.
        returnValue = ~returnValue;
        returnValue = returnValue + 1;
    }
    return returnValue;
}


int ReadBinary(FILE *ptr) {
    char buffer[BUFFER_SIZE];  // print leading signature.
    for(int i=0; i<BUFFER_SIZE; i++) {  // zero the array.
        buffer[i] = 0;
    }
    if (fgets(buffer, BUFFER_SIZE, ptr) == NULL) {  // read up to BUFFER_SIZE characters.
        fprintf(stderr, "Failed to Read from Input.\n");  // bad input / no input.
        exit(BAD_DATA); // exit program.
    }
    return ParseBinary(buffer, strlen(buffer));
}


void PrintBinary(int bin_value, FILE *ptr) {
    fprintf(ptr, "0b");  // print leading signature.
    int start = 0;
    for(int i=31; i>=0; i--) {  // from the most significant to least.
        unsigned int mask = (1 << i);  // create mask.
        if ((mask & bin_value) == mask) {  // if true, then bit is '1'.
            start = 1;
            fprintf(ptr, "1");  // started printing ones, truncate 0's in front.
        }
        else if (start == 1) {  // if 1's have been printing:
            fprintf(ptr, "0");  // print a 0.
        }
    }
}


struct BinArray *BinArray_Malloc(int size) {
    struct BinArray *returnValue = NULL;  // local variable to hold return value;
    returnValue = (struct BinArray *) malloc(sizeof(struct BinArray));  // allocate 1 struct on the heap.
    returnValue->Length = size;  // initiate size value.
    returnValue->Data = (int *) malloc(sizeof(int) * size);  // allocate N*integers on the heap.
    for(int i=0; i<size; i++) {
        returnValue->Data[i] = 0;  // initialize all memory to 0's.
    }
    return returnValue;  // return the pointer to the struct on the heap.
}


void BinArray_Free(struct BinArray **ptr) {
    if ((ptr != NULL) && ((*ptr) != NULL) && ((*ptr)->Data != NULL)) { // don't dereference a bad pointer.
        for (int i=0; i<(*ptr)->Length; i++) { // un-init all memory to 0's.
            (*ptr)->Data[i] = 0;
        }
        free((*ptr)->Data); // de-allocate the array of integers.
        (*ptr)->Data = 0;  // set the pointer to null.
        (*ptr)->Length = 0;  // set the size to 0.
        free((*ptr));  // free the struct pointer.
        (*ptr) = 0;  // set the value of the passed in pointer to null.
    }
    else {
        fprintf(stderr, "Error in BinArray_Free, bad pointer found.\n");
        exit(INVALID_POINTER);
    }
}


void BinArray_Print(struct BinArray *ptr) {
    // Loop through each item and print using PrintBinary.
}


int main(void) {
    int count;  // local variable to store count.
    fprintf(stdout, "Read Binary Number Value:");
    count = ReadBinary(stdin); // read a count.
    fprintf(stdout, "\nBinary Value Printed: ");
    PrintBinary(count, stdout); // print the count.
    struct BinArray *test = BinArray_Malloc(count);  // allocate a BinArray of size count.
    BinArray_Free(&test);  // free the BinArray.
    printf("\n");
    return EXIT_SUCCESS;
}
