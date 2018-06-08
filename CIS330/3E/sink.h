#ifndef SINK_H
#define SINK_H
#include <image.h>

class Sink {

  protected:
	Image *img1;
	Image *img2;

  public:
  	void SetInput(Image *img);
  	void SetInput2(Image *img);

  	Image * GetOutput(void);
  	Image * GetOutput2(void);
 
};

#endif
