#include <iostream>
#include <vtkDataSet.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>

using std::cerr;
using std::endl;

vtkImageData *
NewImage(int width, int height)
{
    vtkImageData *img = vtkImageData::New();
    img->SetDimensions(width, height, 1);
    img->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

    return img;
}

void
WriteImage(vtkImageData *img, const char *filename)
{
   std::string full_filename = filename;
   full_filename += ".png";
   vtkPNGWriter *writer = vtkPNGWriter::New();
   writer->SetInputData(img);
   writer->SetFileName(full_filename.c_str());
   writer->Write();
   writer->Delete();
}


int main()
{
	std::cerr << "In main!" << endl;
	vtkImageData *image = NewImage(1024, 1350);
	unsigned char *buffer = (unsigned char *) image->GetScalarPointer(0,0,0);
	for (int x=0; x<27; ++x) {
		// new starting point for each strip is 50 pixels up, 27 strips so
		// x * 50 to get the starting point for each strip
		buffer = (unsigned char *) image->GetScalarPointer(0, x*50, 0);
		for (int t=0; t<50; ++t) {
			for (int i=0; i<1024; ++i) {
				int index = 3 * ((t * 1024) + i);

				// red channel
				if (x/9 == 0) {
					buffer[index+0] = 0;
				}
				else if (x/9 == 1) {
					buffer[index+0] = 128;
				}
				else if (x/9 == 2) {
					buffer[index+0] = 255;
				}

				// green channel
				if ((x/3)%3 == 0) {
					buffer[index+1] = 0;
				}
				else if ((x/3)%3 == 1) {
					buffer[index+1] = 128;
				}
				else if ((x/3)%3 == 2) {
					buffer[index+1] = 255;
				}

				// blue channel
				if (x%3 == 0) {
					buffer[index+2] = 0;
				}
				else if (x%3 == 1) {
					buffer[index+2] = 128;
				}
				else if (x%3 == 2) {
					buffer[index+2] = 255;
				}
			}
		}
	}
	WriteImage(image, "proj1A");
}
