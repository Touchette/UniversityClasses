#ifndef PNMWRITER_h
#define PNMWRITER_h

#include <sink.h>
#include <image.h>

class PNMwriter : public Sink {
  public:
    // Constructors
    PNMwriter();
    ~PNMwriter();

    // Getters
    Image * GetOutput() { return Sink::GetOutput(); };

    // Write & SinkName
    void Write(char *filename);
    const char * SinkName() { return "PNMwriter"; };
};

#endif