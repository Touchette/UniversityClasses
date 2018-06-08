#ifndef FILTER_h
#define FILTER_h
#include <image.h>
#include <source.h>
#include <sink.h>

class Filter : public Source, public Sink { };

class Shrinker : public Filter {

  public:
  	Shrinker(void) { };

  	void Execute(void);

  	Image * GetOutput(void) { return Source::GetOutput(); };
  	void SetInput(Image *img) { Sink::SetInput(img); };

 };

class LRCombine : public Filter { 

  public:
  	LRCombine(void) { };

  	void Execute(void);

  	Image * GetOutput(void) { return Source::GetOutput(); };
  	void SetInput(Image *img) { Sink::SetInput(img); };
  	void SetInput2(Image *img) { Sink::SetInput2(img); };

};

class TBCombine : public Filter {
  
  public:
  	TBCombine(void) { };

  	void Execute(void);

  	Image * GetOutput(void) { return Source::GetOutput(); };
  	void SetInput(Image *img) { Sink::SetInput(img); };
  	void SetInput2(Image *img) { Sink::SetInput2(img); };

};

class Blender : public Filter { 
  
  private:
  	double factor;

  public:
    Blender(void) { } ;
	  Blender(double fctr) : factor(fctr) { };
	  void SetFactor(double factor) { this->factor = factor; };

	  void Execute(void);

    Image * GetOutput(void) { return Source::GetOutput(); };
    double GetFactor(void) { return this->factor; };

  	void SetInput(Image *img) { Sink::SetInput(img); };

};

#endif
