#include <sink.h>
#include <image.h>

void Sink::SetInput(Image *img) { 
	img1 = img; 
}

void Sink::SetInput2(Image *img) { 
	img2 = img; 
}

Image * Sink::GetOutput(void) { 
	return this->img1; 
}

Image * Sink::GetOutput2(void) { 
	return this->img2; 
}