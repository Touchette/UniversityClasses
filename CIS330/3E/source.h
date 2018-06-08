#ifndef SOURCE_H
#define SOURCE_H
#include <image.h>

class Source {

  protected:
    Image *output = new Image;
    virtual void Execute(void) = 0;

  public:
    virtual void Update() = 0;
    Image * GetOutput();
    Source(void);

};

#endif
