#ifndef SINK_H
#define SINK_H

#include <image.h>

class Sink {
  protected:
    Image *input1;
    Image *input2;

  public:
    // Constructors
    Sink();
    ~Sink();

    // Setters
    void SetInput(Image *img);
    void SetInput2(Image *img);

    // Getters
    Image * GetOutput();
    Image * GetOutput2();

    // sinkName
    virtual const char * sinkName() { };
};

#endif