#include <stdio.h>

void printBytes(unsigned char *start, int len) {
	for (int i = 0; i<len; i++) {
		printf(" %.2x", start[i]);
	}
	printf("\n");
}

void printInt(int x) {
	printBytes((unsigned char * ) &x, sizeof(int));
}

void printFloat(float x) {
	printBytes((unsigned char *) &x, sizeof(float));
}

void printShort(short x) {
	printBytes((unsigned char *) &x, sizeof(short));
}

void printLong(long x) {
	printBytes((unsigned char *) &x, sizeof(long));
}

void printDouble(double x) {
	printBytes((unsigned char *) &x, sizeof(double));
}

int main(int argc, char * argv[]){
	// ugly print statements so I can tell which output is which
	printf("int:\n");
	printInt(10); // starts with 0a, "a" being 10 in hex, makes sense this is in most important bit slot
	printf("short:\n"); 
	printShort(10); // understandable that the short is an integer stored in half the bits
	printf("long:\n");
	printLong(10.0); // again, long is just stored in more bytes, 64 now, starts with 0a still
	printf("double:\n");
	printDouble(10.0); // not sure why this output is 00...24 40
	printf("float:\n");
	printFloat(10.0); // even weirder that it's 00 00 20 41
}