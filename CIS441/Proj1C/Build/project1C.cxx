#include <iostream>
#include <algorithm>
#include <vtkDataSet.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkCellArray.h>

#define goingDown 0
#define goingUp 1
#define arbitrary 2

using std::cerr;
using std::endl;

// +------------------+
// | **************** |
// | Global Functions |
// | **************** |
// +------------------+

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

// +------------------------------+
// | **************************** |
// | Triangle Class & Its Methods |
// | **************************** |
// +------------------------------+

static const char *TriangleTypes[] = { 
	"goingDown", "goingUp", "arbitrary" 
};

class Triangle {
  public:
	double X[3];
	double Y[3];

	unsigned char color[3];

	// Vertices
	int vertex1 = 0;
	int vertex2 = 1;
	int vertex3 = 2;

	// Type of triangle this is, default is arbitrary
	int triangleType = arbitrary;

	void findVertices();
	double findB(int side); // 1 is left side, 0 is right side
	double findSlope(int side); // 1 is left side, 0 is right side
};

void Triangle::findVertices() {
	// Ethan Quick helped me by explaining the vertex sorting logic...
	// I don't know if there's a better way to do it, but his explanation
	// made pretty intuitive sense.
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
		this->triangleType = goingDown;
	} else if (Y[vertex2] == Y[vertex3]) {
		std::swap(vertex3, vertex1);
		if (X[vertex1] > X[vertex2]) {
			std::swap(vertex1, vertex2);
		}
		this->triangleType = goingUp;
	}
}

double Triangle::findSlope(int side) {
	double *X = this->X;
	double *Y = this->Y;

	// calculate the left or right slope
	// 1 is left side, 0 is right side
	if (side) {
		double leftRise  = Y[this->vertex1] - Y[this->vertex3];
		double leftRun   = X[this->vertex1] - X[this->vertex3];
		double leftSlope = leftRise / leftRun;
		return leftSlope;
	} else {
		double rightRise  = Y[this->vertex2] - Y[this->vertex3];
		double rightRun   = X[this->vertex2] - X[this->vertex3];
		double rightSlope = rightRise / rightRun;
		return rightSlope;
	}

	cerr << "didn't find a left or right slope?" << endl;
	return 0.0;
}

double Triangle::findB(int side) {
	double *X = this->X;
	double *Y = this->Y;

	// calculate B value
	// 1 is left side, 0 is right side
	if (side) {
		double leftSlope = this->findSlope(1);
		double leftB = Y[this->vertex3] - (leftSlope * X[this->vertex3]);
		return leftB;
	} else {
		double rightSlope = this->findSlope(0);
		double rightB = Y[this->vertex3] - (rightSlope * X[this->vertex3]);
		return rightB;
	}

	cerr << "didn't find a left or right B value?" << endl;
	return 0.0;
}

// +----------------------------+
// | ************************** |
// | Screen Class & Its Methods |
// | ************************** |
// +----------------------------+

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

	// write the three colors to the buffer
	int index = 3 * ((row * this->width) + column);
	this->buffer[index+0] = color[0];
	this->buffer[index+1] = color[1];
	this->buffer[index+2] = color[2];
}


// +------------------+
// | **************** |
// | Global Functions |
// | **************** |
// +------------------+

// ========================
// Triangle-related methods
// ========================
void rasterizeTriangle(Triangle triangle, Screen screen) {
	// get the vertices sorted before finding them
	triangle.findVertices();
	int vertex1 = triangle.vertex1;
	int vertex2 = triangle.vertex2;
	int vertex3 = triangle.vertex3;

	// redeclare the X and Y arrays to shorten lines
	double *X = triangle.X;
	double *Y = triangle.Y;

	int rowMin, rowMax;
	// rowMin and rowMax are swapped depending on triangle type
	switch (triangle.triangleType) {
		case goingDown:
			rowMin = (int) ceil_441(Y[vertex3]);
			rowMax = (int) floor_441(Y[vertex1]);
			break;
		case goingUp:
			rowMin = (int) ceil_441(Y[vertex1]);
			rowMax = (int) floor_441(Y[vertex3]);
			break;
		default:
			cerr << "Something wrong! Not a valid triangle type: " << endl;
			cerr << triangle.triangleType << endl;
			exit(1);
	}


	// get the left slope and right slope
	double leftSlope  = triangle.findSlope(1);
	double rightSlope = triangle.findSlope(0);

	// get the left B value and the right B value (needed for y=mx+b)
	double leftB  = triangle.findB(1);
	double rightB = triangle.findB(0);

	int r;
	for (r = rowMin; r <= rowMax; ++r) {
		// r = (leftSlope * x) + b (y = mx+b)
		double leftEnd  = (r - leftB) / leftSlope;
		double rightEnd = (r - rightB) / rightSlope;

		// handle right angles
		if (X[vertex1] == X[vertex3]) {
			leftEnd = X[vertex1]; // left hand side right angle
		}
		if (X[vertex2] == X[vertex3]) {
			rightEnd = X[vertex2]; // right hand side right angle
		}

		int c;
		int ceilLeft   = (int) ceil_441(leftEnd);
		int floorRight = (int) floor_441(rightEnd);
		for (c = ceilLeft; c <= floorRight; ++c) {
			screen.ImageColor(r, c, triangle.color);
		}
	}
	// cerr << "Triangle Type: " << TriangleTypes[triangle.triangleType] << endl;
	// cerr << "Vertex 1: (" << triangle.X[vertex1] << ", " << triangle.Y[vertex1] << ")\n";
	// cerr << "Vertex 2: (" << triangle.X[vertex2] << ", " << triangle.Y[vertex2] << ")\n";
	// cerr << "Vertex 3: (" << triangle.X[vertex3] << ", " << triangle.Y[vertex3] << ")\n";
}

void drawTriangle(Triangle triangle, Screen screen) {
	// sort the vertices before doing anything
	triangle.findVertices();

	double slope, b, x;
	Triangle top, bottom;
	int vertex1, vertex2, vertex3;

	// redeclare vertices for easy access
	vertex1 = triangle.vertex1;
	vertex2 = triangle.vertex2;
	vertex3 = triangle.vertex3;
	switch (triangle.triangleType) {
		case arbitrary:
			// Split the triangles into top and bottom, call them as such
			slope = triangle.findSlope(1);
			b     = triangle.findB(1);

			// The new vertex for both triangles
			x = (triangle.Y[vertex2] - b) / slope;

			// Top triangle
			top = Triangle();
			top.triangleType = goingUp;
			// Make sure that the colors are copied over
			top.color[0] = triangle.color[0]; 
			top.color[1] = triangle.color[1];
			top.color[2] = triangle.color[2];
			// Set the vertices up correctly
			top.Y[0] = triangle.Y[vertex1]; top.X[0] = triangle.X[vertex1];
			top.Y[1] = triangle.Y[vertex2]; top.X[1] = x;
			top.Y[2] = triangle.Y[vertex2]; top.X[2] = triangle.X[vertex2];
			// Bottom triangle
			bottom = Triangle();
			bottom.triangleType = goingDown;
			// Make sure that the colors are copied over
			bottom.color[0] = triangle.color[0]; 
			bottom.color[1] = triangle.color[1];
			bottom.color[2] = triangle.color[2];
			// Set the vertices up correctly
			bottom.Y[0] = triangle.Y[vertex3]; bottom.X[0] = triangle.X[vertex3];
			bottom.Y[1] = triangle.Y[vertex2]; bottom.X[1] = x;
			bottom.Y[2] = triangle.Y[vertex2]; bottom.X[2] = triangle.X[vertex2];
			// Rasterize each individual triangle
			rasterizeTriangle(top, screen);
			rasterizeTriangle(bottom, screen);
			break;
		default:
			rasterizeTriangle(triangle, screen);
			break;
	}
}

// ===================================
// Hank's Given Methods (Reading, etc)
// ===================================
std::vector<Triangle> GetTriangles(void) {
    vtkPolyDataReader *rdr = vtkPolyDataReader::New();
    rdr->SetFileName("proj1c_geometry.vtk");
    cerr << "Reading" << endl;
    rdr->Update();
    if (rdr->GetOutput()->GetNumberOfCells() == 0)
    {
        cerr << "Unable to open file!!" << endl;
        exit(EXIT_FAILURE);
    }
    vtkPolyData *pd = rdr->GetOutput();
    int numTris = pd->GetNumberOfCells();
    vtkPoints *pts = pd->GetPoints();
    vtkCellArray *cells = pd->GetPolys();
    vtkFloatArray *colors = (vtkFloatArray *) pd->GetPointData()->GetArray("color_nodal");
    float *color_ptr = colors->GetPointer(0);
    std::vector<Triangle> tris(numTris);
    vtkIdType npts;
    vtkIdType *ptIds;
    int idx;
    for (idx = 0, cells->InitTraversal() ; cells->GetNextCell(npts, ptIds) ; idx++)
    {
        if (npts != 3)
        {
            cerr << "Non-triangles!! ???" << endl;
            exit(EXIT_FAILURE);
        }
        tris[idx].X[0] = pts->GetPoint(ptIds[0])[0];
        tris[idx].X[1] = pts->GetPoint(ptIds[1])[0];
        tris[idx].X[2] = pts->GetPoint(ptIds[2])[0];
        tris[idx].Y[0] = pts->GetPoint(ptIds[0])[1];
        tris[idx].Y[1] = pts->GetPoint(ptIds[1])[1];
        tris[idx].Y[2] = pts->GetPoint(ptIds[2])[1];
        tris[idx].color[0] = (unsigned char) color_ptr[4*ptIds[0]+0];
        tris[idx].color[1] = (unsigned char) color_ptr[4*ptIds[0]+1];
        tris[idx].color[2] = (unsigned char) color_ptr[4*ptIds[0]+2];
    }
    cerr << "Done reading" << endl;

    return tris;
}

// +-------------+
// | *********** |
// | Main Method |
// | *********** |
// +-------------+

int main(int argc, char *argv[]) {
	vtkImageData *image   = NewImage(1786, 1344);
	unsigned char *buffer = (unsigned char *) image->GetScalarPointer(0,0,0);

	// black out the buffer
	int npixels = 1786*1344;
	for (int i = 0 ; i < npixels*3 ; i++) {
	   buffer[i] = 0;
	}

	std::vector<Triangle> triangles = GetTriangles();

	Screen screen;
	screen.buffer = buffer;
	screen.width = 1786;
	screen.height = 1344;

	Triangle test = Triangle();
	test.X[0] = 500; test.Y[0] = 500;
	test.X[1] = 550; test.Y[1] = 550;
	test.X[2] = 600; test.Y[2] = 450;
	test.color[0] = 255; test.color[1] = 0; test.color[2] = 0;

	// drawTriangle(test, &screen);

	for (auto triangle : triangles) {
		drawTriangle(triangle, screen);
	}

	WriteImage(image, "allTriangles");
}
