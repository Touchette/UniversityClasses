#include <source.h>
#include <image.h>

Source::Source() {
	output->setSource(this);
}

Image * Source::GetOutput() { 
	return output;
}