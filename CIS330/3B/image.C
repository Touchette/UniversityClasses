#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <image.h>

Image::Image(void) {
	// Pretty much copy pasted from 3A, but initialized to
	// 0 and NULL for the "pure" constructor
	height = 0;
	width  = 0;
	array  = NULL;
}

Image::Image(int he, int wi, unsigned char *arr) {
	// Size is useful to keep malloc short
	int size = 3 * he * wi;

	// This is pretty straightforward. Just setting the image's
	// height and width to the specified one
	height   = he;
	width    = wi;
	array    = (unsigned char *)(malloc(size));

	// Hank said it's okay to use memcpy in class so I'll use it here
	// instead of a huge for loop
	memcpy(array, arr, size);
}

Image::Image(Image &image) {
	// Copy constructor, again using memcpy
	height = image.height;
	width  = image.width;
	array  = (unsigned char *)(malloc(3 * height * width));
	memcpy(array, image.array, 3 * height * width);
}

void Image::setSize(int he, int wi) {
	// Definition of size setter, easy enough
	height = he;
	width  = wi;
}

void Image::setData(unsigned char *arr) {
	// Initialize our array if it hasn't been initialized already.
	// This will prevent NULL pointer problems
	if (array == NULL) {
		array = (unsigned char*)(malloc(3 * height * width));
	}

	// memcpy again
	memcpy(array, arr, 3 * height * width);
}

int Image::getHeight() {
	// All of these are self explanatory
	return height;
}

int Image::getWidth() {
	return width;
}

unsigned char* Image::getData() {
	return array;
}