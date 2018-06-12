#ifndef IMAGE_H
#define IMAGE_H

#include <logging.h>

class Source;

class Image {
  private:
    int height;
    int width;
    unsigned char *array;
    Source *source;

  public:
    // Constructors
    Image();
    Image(int he, int wi, unsigned char *arr);
    Image(Image &image);
    virtual ~Image();

    // Setters
    void SetSize(int he, int wi);
    void SetData(unsigned char *arr);
    void SetSource(Source *s);

    // Getters
    int GetHeight() const { return height; }
    int GetWidth() const { return width; }
    unsigned char * GetData() const { return array; }

    // Update
    void Update() const;
};

#endif