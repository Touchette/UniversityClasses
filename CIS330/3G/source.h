#ifndef SOURCE_H
#define SOURCE_H

#include <image.h>

class Source {
  protected:
    Image *output = new Image;
    virtual void Execute() = 0;

  public:
    // Constructors
    Source();
    ~Source();

    // Getters
    Image * GetOutput();

    // Update & SourceName
    virtual void         Update();
    virtual const char * SourceName() { };
};

#endif