#ifndef PNMWRITER_h
#define PNMWRITER_h
#include <sink.h>
#include <image.h>


class PNMwriter : public Sink {

  public:
 	PNMwriter();
  	~PNMwriter();

  	void Write(char *filename);
  	Image * GetOutput() { return Sink::GetOutput(); };

};

#endif
