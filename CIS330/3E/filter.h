#ifndef FILTER_h
#define FILTER_h
#include <image.h>
#include <source.h>
#include <sink.h>

class Filter : public Source, public Sink {
  // Hank implemented his update here along with using
  // another two classes to check the number of inputs
  // any given filter requires, I think this really cleans
  // up the code
  public:
    virtual void Update();
    virtual int GetNumberOfInputs() = 0;
};

class SingleInputFilter : public Filter {
  public:
    virtual int GetNumberOfInputs() { return 1; };
};

class DoubleInputFilter : public Filter {
  public:
    virtual int GetNumberOfInputs() { return 2; };
};

class Shrinker : public SingleInputFilter {

  public:
  	Shrinker(void) { };

  	virtual void Execute(void);
    // virtual void Update(void);

  	Image * GetOutput(void) { return Source::GetOutput(); };
  	void SetInput(Image *img) { Sink::SetInput(img); };

 };

class LRCombine : public DoubleInputFilter { 

  public:
  	LRCombine(void) { };

    virtual void Execute(void);
    // virtual void Update(void);

  	Image * GetOutput(void) { return Source::GetOutput(); };
  	void SetInput(Image *img) { Sink::SetInput(img); };
  	void SetInput2(Image *img) { Sink::SetInput2(img); };

};

class TBCombine : public DoubleInputFilter {
  
  public:
  	TBCombine(void) { };

    virtual void Execute(void);
    // virtual void Update(void);

  	Image * GetOutput(void) { return Source::GetOutput(); };
  	void SetInput(Image *img) { Sink::SetInput(img); };
  	void SetInput2(Image *img) { Sink::SetInput2(img); };

};

class Blender : public DoubleInputFilter { 
  
  private:
  	double factor;

  public:
    Blender(void) { } ;
	Blender(double fctr) : factor(fctr) { };
	void SetFactor(double factor) { this->factor = factor; };

    virtual void Execute(void);
    //virtual void Update(void);

    Image * GetOutput(void) { return Source::GetOutput(); };
    double GetFactor(void) { return this->factor; };

  	void SetInput(Image *img) { Sink::SetInput(img); };

};

#endif
