#include <image.h>
#include <sink.h>

Sink::Sink() {
    input1 = NULL;
    input2 = NULL;
}

Sink::~Sink() { };

void Sink::SetInput(Image *img) { 
    input1 = img; 
}

void Sink::SetInput2(Image *img) { 
    input2 = img; 
}

Image * Sink::GetOutput() { 
    return input1; 
}

Image * Sink::GetOutput2() { 
    return input2; 
}