#include <stdio.h>
#include <stdlib.h>
#include <filter.h>
#include <sink.h>
#include <source.h>
#include <image.h>

void Filter::Update() {
	// From Hank's live code session, modified to not use
	// C++ i/o as I don't like it very much. Also different
	// names to match mine
    if (img1 == NULL) {
        fprintf(stderr, "BAD : no input1 to filter\n");
        exit(EXIT_FAILURE);
    }

    img1->Update();

    if (GetNumberOfInputs() == 2) {
        if (img2 == NULL) {
        fprintf(stderr, "BAD : no input2 to filter\n");
        exit(EXIT_FAILURE);
    }
        img2->Update();
    }
    Execute();
}

void Shrinker::Execute() {
	// Halve height of input image after getting it
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
			// Indexing (massive pain)
			inIndex  = 3 * ((width * i * 2) + (j * 2));
			outIndex = 3 * ((halfWidth * i) + j);

			temp[outIndex]     = input->getData()[inIndex];
			temp[outIndex + 1] = input->getData()[inIndex + 1];
			temp[outIndex + 2] = input->getData()[inIndex + 2];
		}
	}

	output->setData(temp);
	free(temp);
}

void LRCombine::Execute() {
	// Get all the heights and widths from both images
	Image *leftInput  = Sink::GetOutput();
	Image *rightinput = Sink::GetOutput2();
	Image *output     = LRCombine::GetOutput();

	int heightOne = leftInput->getHeight();
	int heightTwo = rightinput->getHeight();
	int widthOne  = leftInput->getWidth();
	int widthTwo  = rightinput->getWidth();

	// Getting the values of the output image (will be larger)
	int outputHeight = (heightOne + heightTwo) / 2;
	int outputWidth  = (widthOne + widthTwo);
	int size = outputHeight * outputWidth * 3;

	// Set the size using aforementioned values
	output->setSize(outputHeight, outputWidth);

	unsigned char* temp = (unsigned char *)(malloc(size));

	int inIndex  = 0;
	int outIndex = 0;

	for (int i=0; i<widthOne; ++i) {
		for(int j=0; j<outputHeight; ++j) {
			inIndex  = 3 * ((widthOne * j) + i);
			outIndex = 3 * ((outputWidth * j) + i);

			temp[outIndex]     = leftInput->getData()[inIndex];
			temp[outIndex + 1] = leftInput->getData()[inIndex + 1];
			temp[outIndex + 2] = leftInput->getData()[inIndex + 2];
		}
	}

	inIndex  = 0;
	outIndex = 0;

	for (int u=0; u<widthTwo; ++u) {
		for(int v=0; v<outputHeight; ++v) {
			inIndex  = 3 * ((widthTwo * v) + u);
			outIndex = 3 * ((outputWidth * v)+ widthOne + u);

			temp[outIndex]     = rightinput->getData()[inIndex];
			temp[outIndex + 1] = rightinput->getData()[inIndex + 1];
			temp[outIndex + 2] = rightinput->getData()[inIndex + 2];
		}
	}

	output->setData(temp);
	free(temp);
}

void TBCombine::Execute() {
	Image *topInput    = Sink::GetOutput();
	Image *bottomInput = Sink::GetOutput2();
	Image *output      = TBCombine::GetOutput();

	int heightOne = topInput->getHeight();
	int heightTwo = bottomInput->getHeight();
	int widthOne  = topInput->getWidth();
	int widthTwo  = bottomInput->getWidth();

	int outputHeight = (heightOne + heightTwo);
	int outputWidth  = (widthOne + widthTwo) / 2;
	int size         = outputHeight * outputWidth * 3;

	output->setSize(outputHeight, outputWidth);

	unsigned char* temp = (unsigned char *)(malloc(size));

	int inIndex  = 0;
	int outIndex = 0;

	for (int i=0; i<outputWidth; ++i) {
		for(int j=0; j<heightOne; ++j) {
			inIndex  = 3 * (widthOne * j + i);
			outIndex = 3 * (outputWidth * j + i);

			temp[outIndex]     = topInput->getData()[inIndex];
			temp[outIndex + 1] = topInput->getData()[inIndex + 1];
			temp[outIndex + 2] = topInput->getData()[inIndex + 2];
		}
	}

	inIndex  = 0;
	outIndex = 0;

	for (int u=0; u<outputWidth; ++u) {
		for(int v=0; v<heightTwo; ++v) {
			inIndex  = 3 * ((widthTwo * v)+ u);
			outIndex = 3 * ((outputWidth * (v + heightOne)) + u);

			temp[outIndex]     = bottomInput->getData()[inIndex];
			temp[outIndex + 1] = bottomInput->getData()[inIndex + 1];
			temp[outIndex + 2] = bottomInput->getData()[inIndex + 2];
		}
	}

	output->setData(temp);
	free(temp);
}

void Blender::Execute() {
	Image *input1 = Sink::GetOutput();
	Image *input2 = Sink::GetOutput2();
	Image *output = Source::GetOutput();
	double factor = this->GetFactor();

	int heightOne = input1->getHeight();
	int heightTwo = input2->getHeight();
	int widthOne  = input1->getWidth();
	int widthTwo  = input2->getWidth();

	int outputHeight = (heightOne + heightTwo) / 2;
	int outputWidth  = (widthOne + widthTwo) / 2;
	int size         = outputHeight * outputWidth * 3;

	output->setSize(outputHeight, outputWidth);

	unsigned char* temp = (unsigned char *)(malloc(size));

	int index = 0;

	for (int i=0; i<outputWidth; ++i) {
		for(int j=0; j<outputHeight; ++j) {
			index  = 3 * ((outputWidth * j) + i);

			temp[index]     = input1->getData()[index] * factor + input2->getData()[index] * (1 - factor);
			temp[index + 1] = input1->getData()[index + 1] * factor + input2->getData()[index + 1] * (1 - factor);
			temp[index + 2] = input1->getData()[index + 2] * factor + input2->getData()[index + 2] * (1 - factor);
		}
	}

	output->setData(temp);
	free(temp);
}