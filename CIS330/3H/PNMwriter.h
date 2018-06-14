#ifndef PNMWRITER_h
#define PNMWRITER_h

#include <image.h>
#include <sink.h>

class PNMwriter : public Sink {
  public:
    // Constructors
    PNMwriter();
    ~PNMwriter();

    // Getters
    Image * GetOutput() { return Sink::GetOutput(); };

    // Write & SinkName
    void Write(const char *filename);
    const char * SinkName() { return "PNMwriter"; };
};

#endif