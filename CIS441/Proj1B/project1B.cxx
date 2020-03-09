#include <iostream>
#include <algorithm>
#include <vtkDataSet.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>

using std::cerr;
using std::endl;

double ceil_441(double f) {
	return ceil(f-0.00001);
}

double floor_441(double f) {
	return floor(f+0.00001);
}


vtkImageData * NewImage(int width, int height) {
	vtkImageData *img = vtkImageData::New();
	img->SetDimensions(width, height, 1);
	img->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

	return img;
}

void WriteImage(vtkImageData *img, const char *filename) {
	std::string full_filename = filename;
	full_filename += ".png";
	vtkPNGWriter *writer = vtkPNGWriter::New();
	writer->SetInputData(img);
	writer->SetFileName(full_filename.c_str());
	writer->Write();
	writer->Delete();
}

class Triangle {
  public:
	double X[3];
	double Y[3];

	unsigned char color[3];

	// vertices
	int vertex1 = 0;
	int vertex2 = 1;
	int vertex3 = 2;

	void findVertices();
};

void Triangle::findVertices() {
	if (Y[vertex1] < Y[vertex2]) {
		std::swap(vertex1, vertex2);
	}

	if (Y[vertex1] < Y[vertex3]) {
		std::swap(vertex1, vertex3);
	}

	if (Y[vertex2] < Y[vertex3]) {
		std::swap(vertex2, vertex3);
	}

	if (Y[vertex1] == Y[vertex2]) {
		if (X[vertex1] > X[vertex2]) {
			std::swap(vertex1, vertex2);
		}
	}
}

class Screen {
  public:
	unsigned char *buffer;
	int width, height;

	void ImageColor(int row, int column, unsigned char color[3]);
};

void Screen::ImageColor(int row, int column, unsigned char color[3]) {
	// make sure to not go outside the bounds of the image when coloring
	if (row < 0 || row >= this->height) {
		return;
	}
	if (column < 0 || column >= this->width) {
		return;
	}

	int index = 3 * ((row * this->width) + column);
	this->buffer[index+0] = color[0];
	this->buffer[index+1] = color[1];
	this->buffer[index+2] = color[2];
}

std::vector<Triangle> GetTriangles(void) {
	std::vector<Triangle> rv(100);

	unsigned char colors[6][3] = { {255,128,0}, {255, 0, 127}, {0,204,204}, 
								 {76,153,0},  {255, 204, 204}, {204, 204, 0} };
	for (int i = 0 ; i < 100 ; i++) {
		int idxI = i%10;
		int posI = idxI*100;
		int idxJ = i/10;
		int posJ = idxJ*100;
		int firstPt = (i%3);
		rv[i].X[firstPt] = posI;
		if (i == 50) {
		   rv[i].X[firstPt] = -10;
		}
		rv[i].Y[firstPt] = posJ+10*(idxJ+1);
		rv[i].X[(firstPt+1)%3] = posI+99;
		rv[i].Y[(firstPt+1)%3] = posJ+10*(idxJ+1);
		rv[i].X[(firstPt+2)%3] = posI+i;
		rv[i].Y[(firstPt+2)%3] = posJ;
		if (i == 5) {
		  rv[i].Y[(firstPt+2)%3] = -50;
		}
		rv[i].color[0] = colors[i%6][0];
		rv[i].color[1] = colors[i%6][1];
		rv[i].color[2] = colors[i%6][2];
	}

	return rv;
}

int main(int argc, char *argv[]) {
	vtkImageData *image   = NewImage(1000, 1000);
	unsigned char *buffer = (unsigned char *) image->GetScalarPointer(0,0,0);

	int npixels = 1000*1000;
	for (int i = 0 ; i < npixels*3 ; i++) {
	   buffer[i] = 0;
	}

	std::vector<Triangle> triangles = GetTriangles();

	Screen screen;
	screen.buffer = buffer;
	screen.width = 1000;
	screen.height = 1000;

	int count = 0;
	for (auto triangle : triangles) {
		// get the vertices sorted before finding them
		triangle.findVertices();
		int vertex1 = triangle.vertex1;
		int vertex2 = triangle.vertex2;
		int vertex3 = triangle.vertex3;

		// redeclare the X and Y arrays to shorten lines
		double *X = triangle.X;
		double *Y = triangle.Y;

		int rowMin = (int) ceil_441(Y[vertex3]);
		int rowMax = (int) floor_441(Y[vertex1]);

		// calculate the left and right slope
		double leftRise  = Y[vertex1] - Y[vertex3];
		double leftRun   = X[vertex1] - X[vertex3];
		double leftSlope = leftRise / leftRun;

		double rightRise  = Y[vertex2] - Y[vertex3];
		double rightRun   = X[vertex2] - X[vertex3];
		double rightSlope = rightRise / rightRun;

		double leftB  = Y[vertex3] - (leftSlope * X[vertex3]);
		double rightB = Y[vertex3] - (rightSlope * X[vertex3]);

		int r;
		for (r = rowMin; r <= rowMax; ++r) {
			// r = (leftSlope * x) + b (y = mx+b)
			double leftEnd  = (r - leftB) / leftSlope;
			double rightEnd = (r - rightB) / rightSlope;

			// handle right angles
			if (X[0] == X[1] || X[0] == X[2]) {
				leftEnd = X[vertex1];
			}
			if (X[1] == X[2]) {
				rightEnd = X[vertex2];
			}

			int c;
			int ceilLeft   = (int) ceil_441(leftEnd);
			int floorRight = (int) floor_441(rightEnd);
			for (c = ceilLeft; c <= floorRight; ++c) {
				screen.ImageColor(r, c, triangle.color);
			}
		}
		count++;
	}

	WriteImage(image, "allTriangles");
}
