#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int i;

	for (i=0; i<argc; ++i) {
		fprintf(stdout, "%s\n", argv[i]);
	}
}
