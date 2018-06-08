#ifndef FILTER_hT
#define FILTER_h
#include <image.h>
#include <source.h>
#include <sink.h>

class Filter : public Source, public Sink {
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
};

class SingleInputFilter : public Filter {
  // Filter that Shrinker inherits from
  public:
    virtual int GetNumberOfInputs() { return 1; };
    virtual const char * FilterName() = 0;
    virtual const char * SourceName() { return FilterName(); };
    virtual const char * SinkName() { return FilterName(); };
};

class DoubleInputFilter : public Filter {
  // Filter that LRCombine, TBCombine, Blender inherits from
  public:
    virtual int GetNumberOfInputs() { return 2; };
    virtual const char * FilterName() = 0;
    virtual const char * SourceName() { return FilterName(); };
    virtual const char * SinkName() { return FilterName(); };
};

class Shrinker : public SingleInputFilter {
  public:
    // Constructors
  	Shrinker(void) { };

    // Setters
    void SetInput(Image *img) { Sink::SetInput(img); };

    // Getters
    Image * GetOutput(void) { return Source::GetOutput(); };

    // FilterName & Execute
    virtual const char * FilterName() { return "Shrinker"; };
    virtual void Execute(void);
 };

class LRCombine : public DoubleInputFilter { 
  public:
    // Constructors
  	LRCombine(void) { };

    // Setters
    void SetInput(Image *img) { Sink::SetInput(img); };
    void SetInput2(Image *img) { Sink::SetInput2(img); };

    // Getters
    Image * GetOutput(void) { return Source::GetOutput(); };

    // FilterName & Execute
    virtual const char * FilterName() { return "LRCombine"; };
    virtual void Execute(void);
};

class TBCombine : public DoubleInputFilter {
  public:
    //Constructors
  	TBCombine(void) { };

    // Setters
    void SetInput(Image *img) { Sink::SetInput(img); };
    void SetInput2(Image *img) { Sink::SetInput2(img); };

    // Getters
  	Image * GetOutput(void) { return Source::GetOutput(); };

    // FilterName & Execute
    virtual const char * FilterName() { return "TBCombine"; };
    virtual void Execute(void);
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
    virtual void Execute(void);
};

class CheckSum : public Sink {
  private:
    Image * input;

  public:
    // Setters
    void SetInput(Image* img);

    // OutputCheckSum & SinkName
    void OutputCheckSum(char* filename);

};

#endif
