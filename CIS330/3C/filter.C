#include <stdio.h>
#include <stdlib.h>
#include <filter.h>
#include <sink.h>
#include <source.h>
#include <image.h>

void Shrinker::Execute() {
	// Get the height and width from the input image, as well as halve them
	// to be used for the output image
	Image *input   = Sink::GetOutput();
	Image *output  = Shrinker::GetOutput();

	int height     = input->getHeight();
	int width      = input->getWidth();
	int halfHeight = height / 2;
	int halfWidth  = width / 2;

	// The temporary array that will be used for the new image
	unsigned char *temp = (unsigned char *)(malloc(halfHeight * halfWidth * 3));

	// Set the size of the output image to be the halved one
	output->setSize(halfHeight, halfWidth);

	int inIndex = 0;
	int outIndex = 0;

	for (int i=0; i<halfHeight; ++i) {
		for (int j=0; j<halfWidth; ++j) {
			// The indexing to be used by both of the images here,
			// the outward one is dependent on halfwidth whereas the
			// input one is only dependent on the normal width. The
			// math here is discussed in the YouTube lecture
			inIndex  = 3 * ((width * i * 2) + (j * 2));
			outIndex = 3 * ((halfWidth * i) + j);

			// Setting the temporary output array to be the proper pixel
			// on the input array
			temp[outIndex]     = input->getData()[inIndex];
			temp[outIndex + 1] = input->getData()[inIndex + 1];
			temp[outIndex + 2] = input->getData()[inIndex + 2];
		}
	}

	// Setting the data of the output image as well as freeing the temporary
	// array, as we don't need it anymore
	output->setData(temp);
	free(temp);
}

void LRCombine::Execute() {
	// Get all the heights and widths from both images using their getter
	// functions
	Image *leftInput  = Sink::GetOutput();
	Image *rightinput = Sink::GetOutput2();
	Image *output     = LRCombine::GetOutput();

	int heightOne = leftInput->getHeight();
	int heightTwo = rightinput->getHeight();
	int widthOne  = leftInput->getWidth();
	int widthTwo  = rightinput->getWidth();

	// if (heightOne != heightTwo) { fprintf(stderr, "Cannot work on images with different heights.\n"); exit(1); }

	// Getting the values of the output image that will be larger than
	// the other two, the height needs to be the same though so we have to
	// sum them up and divide by 2 (**INTEGER DIVISION**).
	int outputHeight = (heightOne + heightTwo) / 2;
	int outputWidth  = (widthOne + widthTwo);
	int size = outputHeight * outputWidth * 3;

	// Set the size using aforementioned values
	output->setSize(outputHeight, outputWidth);

	// Temporary array once more
	unsigned char* temp = (unsigned char *)(malloc(size));

	int inIndex  = 0;
	int outIndex = 0;

	// These for loops will be for left input
	for (int i=0; i<widthOne; ++i) {
		for(int j=0; j<outputHeight; ++j) {
			// Indexing into the images as in HalfSize()
			inIndex  = 3 * ((widthOne * j) + i);
			outIndex = 3 * ((outputWidth * j) + i);

			// Setting the left input here
			temp[outIndex]     = leftInput->getData()[inIndex];
			temp[outIndex + 1] = leftInput->getData()[inIndex + 1];
			temp[outIndex + 2] = leftInput->getData()[inIndex + 2];
		}
	}

	// Resetting the indices
	inIndex  = 0;
	outIndex = 0;

	// These for loops will be for right input 
	// (I don't want to use i and j for this loop, looks nicer in my opinion)
	for (int u=0; u<widthTwo; ++u) {
		for(int v=0; v<outputHeight; ++v) {
			// Indexing into the images as in HalfSize()
			inIndex  = 3 * ((widthTwo * v) + u);
			outIndex = 3 * ((outputWidth * v)+ widthOne + u);

			// Setting the right input here
			temp[outIndex]     = rightinput->getData()[inIndex];
			temp[outIndex + 1] = rightinput->getData()[inIndex + 1];
			temp[outIndex + 2] = rightinput->getData()[inIndex + 2];
		}
	}

	// Setting the data of the output image as well as freeing the temporary
	// array, as we don't need it anymore
	output->setData(temp);
	free(temp);
}

void TBCombine::Execute() {
	// Get all the heights and widths from both images using their getter
	// functions
	Image *topInput    = Sink::GetOutput();
	Image *bottomInput = Sink::GetOutput2();
	Image *output      = TBCombine::GetOutput();

	int heightOne = topInput->getHeight();
	int heightTwo = bottomInput->getHeight();
	int widthOne  = topInput->getWidth();
	int widthTwo  = bottomInput->getWidth();

	// if (widthOne != widthTwo) { fprintf(stderr, "Cannot work on images with different widths.\n"); exit(1); }

	// Getting the values of the output image that will be larger than
	// the other two, the width needs to be the same though so we have to
	// sum them up and divide by 2 (**INTEGER DIVISION**).
	int outputHeight = (heightOne + heightTwo);
	int outputWidth  = (widthOne + widthTwo) / 2;
	int size         = outputHeight * outputWidth * 3;

	// Set the size using aforementioned values
	output->setSize(outputHeight, outputWidth);

	// Temporary array once more
	unsigned char* temp = (unsigned char *)(malloc(size));

	int inIndex  = 0;
	int outIndex = 0;

	// These for loops will be for top input
	for (int i=0; i<outputWidth; ++i) {
		for(int j=0; j<heightOne; ++j) {
			// Indexing into the images as in HalfSize()
			inIndex  = 3 * (widthOne * j + i);
			outIndex = 3 * (outputWidth * j + i);

			// Setting the top input here
			temp[outIndex]     = topInput->getData()[inIndex];
			temp[outIndex + 1] = topInput->getData()[inIndex + 1];
			temp[outIndex + 2] = topInput->getData()[inIndex + 2];
		}
	}

	// Resetting the indices
	inIndex  = 0;
	outIndex = 0;

	// These for loops will be for bottom input 
	// (I don't want to use i and j for this loop, looks nicer in my opinion)
	for (int u=0; u<outputWidth; ++u) {
		for(int v=0; v<heightTwo; ++v) {
			// Indexing into the images as in HalfSize()
			inIndex  = 3 * ((widthTwo * v)+ u);
			outIndex = 3 * ((outputWidth * (v + heightOne)) + u);

			// Setting the bottom input here
			temp[outIndex]     = bottomInput->getData()[inIndex];
			temp[outIndex + 1] = bottomInput->getData()[inIndex + 1];
			temp[outIndex + 2] = bottomInput->getData()[inIndex + 2];
		}
	}

	// Setting the data of the output image as well as freeing the temporary
	// array, as we don't need it anymore
	output->setData(temp);
	free(temp);
}

void Blender::Execute() {
	// Get all the heights and widths from both images using their getter
	// functions
	Image *input1 = Sink::GetOutput();
	Image *input2 = Sink::GetOutput2();
	Image *output = Source::GetOutput();
	double factor = this->GetFactor();


	int heightOne = input1->getHeight();
	int heightTwo = input2->getHeight();
	int widthOne  = input1->getWidth();
	int widthTwo  = input2->getWidth();

	// if (heightOne != heightTwo && widthOne != widthTwo) {
	// 	fprintf(stderr, "Cannot work on images with different widths.\n");
	// 	exit(1);
	// }

	// Getting the values of the output image that will be larger than
	// the other two, the height & width need to be the same though so we
	// have to sum them up and divide by 2 (**INTEGER DIVISION**).
	int outputHeight = (heightOne + heightTwo) / 2;
	int outputWidth  = (widthOne + widthTwo) / 2;
	int size         = outputHeight * outputWidth * 3;

	// Set the size using aforementioned values
	output->setSize(outputHeight, outputWidth);

	// Temporary array once more
	unsigned char* temp = (unsigned char *)(malloc(size));

	int index = 0;

	// These for loops will be for top input
	for (int i=0; i<outputWidth; ++i) {
		for(int j=0; j<outputHeight; ++j) {
			// Indexing into the images as in HalfSize()
			index  = 3 * ((outputWidth * j) + i);

			// Blending the image by the desired factor
			temp[index]     = input1->getData()[index] * factor + input2->getData()[index] * (1 - factor);
			temp[index + 1] = input1->getData()[index + 1] * factor + input2->getData()[index + 1] * (1 - factor);
			temp[index + 2] = input1->getData()[index + 2] * factor + input2->getData()[index + 2] * (1 - factor);
		}
	}

	// Setting the data of the output image as well as freeing the temporary
	// array, as we don't need it anymore
	output->setData(temp);
	free(temp);
}