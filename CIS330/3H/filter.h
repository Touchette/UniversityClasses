#ifndef FILTER_h
#define FILTER_h
#include <source.h>
#include <image.h>
#include <sink.h>

class Filter : public Source, public Sink {
  private:
    int andycounter = 0;
  public:
    virtual void         Update();
    virtual int          GetNumberOfInputs() = 0;
    virtual const char * FilterName() = 0;
    virtual const char * SourceName() { return FilterName(); };
    virtual const char * SinkName() { return FilterName(); };
    virtual void ThrowException();
    virtual void ThrowException2();
    virtual void ThrowHeightException();
    virtual void ThrowWidthException();
    virtual void ThrowSizeException();
    virtual void ThrowFactorException();
    virtual void ThrowLoopException();
};

class SingleInputFilter : public Filter {
  // Filter that Shrinker, Grayscale, Mirror, Rotate, & Blur inherit from
  public:
    virtual int GetNumberOfInputs() { return 1; };
    virtual const char * FilterName() = 0;
    virtual const char * SourceName() { return FilterName(); };
    virtual const char * SinkName() { return FilterName(); };
};

class DoubleInputFilter : public Filter {
  // Filter that LRCombine, TBCombine, Blender, & Subtract inherits from
  public:
    virtual int GetNumberOfInputs() { return 2; };
    virtual const char * FilterName() = 0;
    virtual const char * SourceName() { return FilterName(); };
    virtual const char * SinkName() { return FilterName(); };
};

class Shrinker : public SingleInputFilter {
  public:
    // Constructors
    Shrinker() { };

    // Setters
    void SetInput(Image *img) { Sink::SetInput(img); };

    // Getters
    Image * GetOutput() { return Source::GetOutput(); };

    // FilterName & Execute
    virtual const char * FilterName() { return "Shrinker"; };
    virtual void Execute();
 };

class Mirror : public SingleInputFilter {
  public:
    // Constructors
    Mirror() { };

    // Setters
    void SetInput(Image *img) { Sink::SetInput(img); };

    // Getters
    Image * GetOutput() { return Source::GetOutput(); };

    // FilterName & Execute
    virtual const char * FilterName() { return "Mirror"; };
    virtual void Execute();
};

class Rotate : public SingleInputFilter {
  public:
    // Constructors
    Rotate() { };

    // Setters
    void SetInput(Image *img) { Sink::SetInput(img); };

    // Getters
    Image * GetOutput() { return Source::GetOutput(); };

    // FilterName & Execute
    virtual const char * FilterName() { return "Rotate"; };
    virtual void Execute();
};

class Grayscale : public SingleInputFilter {
  public:
    // Constructors
    Grayscale() { };

    // Setters
    void SetInput(Image *img) { Sink::SetInput(img); };

    // Getters
    Image * GetOutput() { return Source::GetOutput(); };

    // FilterName & Execute
    virtual const char * FilterName() { return "Grayscale"; };
    virtual void Execute();
};

class Blur : public SingleInputFilter {
  public:
    // Constructors
    Blur() { };

    // Setters
    void SetInput(Image *img) { Sink::SetInput(img); };

    // Getters
    Image * GetOutput() { return Source::GetOutput(); };

    // FilterName & Execute
    virtual const char * FilterName() { return "Blur"; };
    virtual void Execute();
};

class LRCombine : public DoubleInputFilter { 
  public:
    // Constructors
    LRCombine() { };

    // Setters
    void SetInput(Image *img) { Sink::SetInput(img); };
    void SetInput2(Image *img) { Sink::SetInput2(img); };

    // Getters
    Image * GetOutput() { return Source::GetOutput(); };

    // FilterName & Execute
    virtual const char * FilterName() { return "LRCombine"; };
    virtual void Execute();
};

class TBCombine : public DoubleInputFilter {
  public:
    // Constructors
    TBCombine() { };

    // Setters
    void SetInput(Image *img) { Sink::SetInput(img); };
    void SetInput2(Image *img) { Sink::SetInput2(img); };

    // Getters
    Image * GetOutput() { return Source::GetOutput(); };

    // FilterName & Execute
    virtual const char * FilterName() { return "TBCombine"; };
    virtual void Execute();
};

class Blender : public DoubleInputFilter { 
  private:
    double factor;

  public:
    // Constructors
    Blender() { };
    Blender(double fctr) : factor(fctr) { };

    // Setters
    void SetInput(Image *img) { Sink::SetInput(img); };
    void SetFactor(double fctr) { factor = fctr; };

    // Getters
    Image * GetOutput() { return Source::GetOutput(); };
    double GetFactor() { return factor; };

    // FilterName & Execute
    virtual const char * FilterName() { return "Blender"; };
    virtual void Execute();
};

class Subtract : public DoubleInputFilter {
  public:
    // Constructors
    Subtract() { };

    // Setters
    void SetInput(Image *img) { Sink::SetInput(img); };
    void SetInput2(Image *img) { Sink::SetInput2(img); };

    // Getters
    Image * GetOutput() { return Source::GetOutput(); };

    // FilterName & Execute
    virtual const char * FilterName() { return "Subtract"; };
    virtual void Execute();
};

class Color : public Source {
  private:
    int height, width;
    unsigned char red, green, blue;

  public:
    // Constructors
    Color(int he, int wi, unsigned char r, unsigned char g, unsigned char b);

    // Getters
    Image * GetOutput() { return Source::GetOutput(); };

    // SourceName & Execute
    virtual const char * SourceName() { return "Color"; };
    virtual void Execute();
};

class CheckSum : public Sink {
  private:
    Image *input;

  public:
    // Constructors
    CheckSum() { };

    // Setters
    void SetInput(Image *img);

    // SinkName & OutputCheckSum
    virtual const char * SinkName() { return "CheckSum"; };
    void OutputCheckSum(const char *filename);
};

#endif