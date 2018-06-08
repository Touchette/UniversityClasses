#ifndef PNMREADER_h
#define PNMREADER_h
#include <source.h>
#include <image.h>


class PNMreader : public Source {

  private:
  	char * filename;

  public:
  	PNMreader(char *filename);
  	~PNMreader();

  	void Execute(void);
  	Image * GetOutput() { return Source::GetOutput(); } ;

};

#endif
