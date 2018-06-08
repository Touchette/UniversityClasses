#ifndef IMAGE_H
#define IMAGE_H

class Image {
	// Pretty much copied from 3A. Here, we have the prototypes
	// for the functions that will be defined in image.C. Hank
	// said not to put even one-line function definitions in a
	// header file, so even those are done in image.C

	private:
	    int height;
	    int width;
	    unsigned char *array;

	public:
		// Constructors
		Image(void);
		Image(int he, int wi, unsigned char *arr);
		Image(Image &image);

		// Setters
		void setSize(int he, int wi);
		void setData(unsigned char *arr);

		// Getters
		int getHeight() { return height; }
		int getWidth() { return width; }
		unsigned char* getData() { return array; }
};

#endif