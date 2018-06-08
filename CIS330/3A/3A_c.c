#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int width;
	int height;
	char *array;
} Image;

Image *ReadImage(char *filename) {
	// "rb" for read binary
 	FILE *f_in;
 	Image *image;
 	f_in = fopen(filename, "rb");
 	
 	// Check if we actually read a file
 	if (f_in == NULL) {
 		fprintf(stderr, "Unable to open file \"%s\".\n", filename);
 		exit(1);
 	}

 	// These 3 lines given by Hank
 	char magicNum[128];
 	int width, height, maxval;
 	// From the YouTube lecture, this is the start of a PNM P6 file
 	fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

 	// Allocate memory for the image, going to set width & height
 	image         = malloc(sizeof(Image));
 	image->width  = width;
 	image->height = height;

 	// This gets used a lot, give it a variable to make code more readable
 	int size = height * width * 3;

 	// Pixel struct useful here
 	image->array = malloc(sizeof(unsigned char) * size);

 	// Read in the binary data from the file which is in the form of
 	// unsigned chars, this is a 3 dimensional array that Hank spoke
 	// about in the YouTube lecture which was easier to read in my opinion
 	// (I tried using a pixel struct and couldn't find out how to read well)
 	fread(image->array, sizeof(unsigned char), size, f_in);

 	// Close file, don't free because calling function does that
 	fclose(f_in);

 	return image;
}


void WriteImage(char *filename, Image &image) {
	// "wb" for write binary
	FILE *f_out;
	f_out = fopen(filename, "wb");

	// Grab the height and width from the input image
	int height = image.getHeight();
	int width  = image.getWidth();

	// Same as before
	int size = height * width * 3;

	// Printing out the start of a PNM P6 file, as explained in the
	// YouTube lecture
	fprintf(f_out, "P6\n%d %d\n255\n", width, height);

	// Writing the binary data from the (edited) image now, this comes after
	// the header
	fwrite(image.getData(), sizeof(unsigned char), size, f_out);

	fclose(f_out);
}

Image *YellowDiagonal(Image *input) {
	// Our output image so as not to modify original
	Image *output = malloc(sizeof(Image));

	// Grab the height and width from the input image
	int height = input->height;
	int width  = input->width;

	// Same as before
	int size = height * width * 3;

	// Our output image will obviously be the same height and width
	output->height = height;
	output->width  = width;
	output->array  = malloc(size);

	// Copy the input "array of pixels" into the output one
	for (int i=0; i<size; ++i) {
		output->array[i] = input->array[i];
	}

	int index = 0;

	for (int i=0; i<width; ++i) {
		// The indexing used for a 3 dimensional image array, which
		// is what I used instead of a pixel struct
		index = 3 * (width * i + i);
		// Yellow is 255 red, 255 green, 0 blue (as discussed by Hank)
		output->array[index]     = 255;
		output->array[index + 1] = 255;
		output->array[index + 2] = 0;
	}

	return output;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Usage is \"%s <input filename> <output filename>\"\n", argv[0]);
		exit(1);
	}

    /* Read an image, apply yellow diagonal to it, then write */
	Image *image = ReadImage(argv[1]);
	image = YellowDiagonal(image);
	WriteImage(image, argv[2]);

	// Calling function's responsibility to free images
	free(image);
}
