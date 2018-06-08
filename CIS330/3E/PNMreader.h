#ifndef PNMREADER_h
#define PNMREADER_h
#include <source.h>
#include <image.h>


class PNMreader : public Source {

  protected:
  	char * filename;

  public:
  	PNMreader(char *filename);
  	~PNMreader();

  	void Execute(void);
  	void Update(void);
  	Image * GetOutput() { return Source::GetOutput(); } ;

};

#endif
