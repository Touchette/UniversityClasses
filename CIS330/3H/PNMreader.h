#ifndef PNMREADER_h
#define PNMREADER_h

#include <source.h>
#include <image.h>


class PNMreader : public Source {
  protected:
    char *filename;

  public:
    // Constructors
    PNMreader(const char *fn);
    ~PNMreader();

    // Getters
    Image * GetOutput() { return Source::GetOutput(); } ;

    // Update, Execute, & SourceName
    void Update();
    void Execute();
    const char * SourceName() { return "PNMreader"; }; 
};

#endif