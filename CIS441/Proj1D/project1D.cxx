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

// Definitions of triangle types
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
	double Z[3];

	double colors[3][3];

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

	// Calculate B value
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
	double *zBuffer;
	int width, height;

	void ImageColor(int row, int column, double z, double color[3]);
};

void Screen::ImageColor(int row, int column, double z, double color[3]) {
	// Make sure to not go outside the bounds of the image when coloring
	if (row < 0 || row >= this->height) {
		return;
	}
	if (column < 0 || column >= this->width) {
		return;
	}

	if (!(z > this->zBuffer[(row * this->width) + column])) {
		return;
	}

	this->zBuffer[(row * this->width) + column] = z;
	// Write the three colors to the buffer
	int index = 3 * ((row * this->width) + column);
	this->buffer[index+0] = (unsigned char) ceil_441(255*color[0]);
	this->buffer[index+1] = (unsigned char) ceil_441(255*color[1]);
	this->buffer[index+2] = (unsigned char) ceil_441(255*color[2]);
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
	// Get the vertices sorted before finding them
	triangle.findVertices();
	int vertex1 = triangle.vertex1;
	int vertex2 = triangle.vertex2;
	int vertex3 = triangle.vertex3;

	// Redeclare the arrays to shorten lines
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


	// Get the left slope and right slope
	double leftSlope  = triangle.findSlope(1);
	double rightSlope = triangle.findSlope(0);

	// Get the left B value and the right B value (needed for y=mx+b)
	double leftB  = triangle.findB(1);
	double rightB = triangle.findB(0);

	int r;
	for (r = rowMin; r <= rowMax; ++r) {
		// r = (leftSlope * x) + b (y = mx+b)
		double leftEnd  = (r - leftB) / leftSlope;
		double rightEnd = (r - rightB) / rightSlope;

		// T = (x - a) / (b - a)
		double leftT = (r - Y[vertex1]) / (Y[vertex3] - Y[vertex1]);
		// LERP Formula -> F(x) = F(a) + t * (F(b) - F(a))
		double leftRed   = triangle.colors[vertex1][0] + (leftT * (triangle.colors[vertex3][0] - triangle.colors[vertex1][0]));
		double leftGreen = triangle.colors[vertex1][1] + (leftT * (triangle.colors[vertex3][1] - triangle.colors[vertex1][1]));
		double leftBlue  = triangle.colors[vertex1][2] + (leftT * (triangle.colors[vertex3][2] - triangle.colors[vertex1][2]));

		// T = (x - a) / (b - a)
		double rightT = (r - Y[vertex2]) / (Y[vertex3] - Y[vertex2]);
		// LERP Formula -> F(x) = F(a) + t * (F(b) - F(a))
		double rightRed   = triangle.colors[vertex2][0] + (rightT * (triangle.colors[vertex3][0] - triangle.colors[vertex2][0]));
		double rightGreen = triangle.colors[vertex2][1] + (rightT * (triangle.colors[vertex3][1] - triangle.colors[vertex2][1]));
		double rightBlue  = triangle.colors[vertex2][2] + (rightT * (triangle.colors[vertex3][2] - triangle.colors[vertex2][2]));

		// Left-hand side colors
		double ColorsLeft[3]  = { leftRed,
								  leftGreen,
								  leftBlue };
		// Right-hand side colors
		double ColorsRight[3] = { rightRed, 
								  rightGreen,
								  rightBlue };

		// Z-buffer calculations
		double leftZ  = triangle.Z[vertex1] + (leftT  * (triangle.Z[vertex3] - triangle.Z[vertex1]));
		double rightZ = triangle.Z[vertex2] + (rightT * (triangle.Z[vertex3] - triangle.Z[vertex2]));

		// Handle right angles
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
			// Color the pixels
			double t = ((c - leftEnd) / (rightEnd - leftEnd));
			double Colors[3] = { ColorsLeft[0] + (t * (ColorsRight[0] - ColorsLeft[0])),
								 ColorsLeft[1] + (t * (ColorsRight[1] - ColorsLeft[1])),
								 ColorsLeft[2] + (t * (ColorsRight[2] - ColorsLeft[2])) };

			double z = leftZ + (t * (rightZ - leftZ));

			screen.ImageColor(r, c, z, Colors);
		}
	}
}

void drawTriangle(Triangle triangle, Screen screen) {
	// Sort the vertices before doing anything
	triangle.findVertices();

	// Forward declarations
	double slope, b, x, topT, bottomT;
	Triangle top, bottom;
	int vertex1, vertex2, vertex3;

	// Redeclare vertices for easy access
	vertex1 = triangle.vertex1;
	vertex2 = triangle.vertex2;
	vertex3 = triangle.vertex3;
	switch (triangle.triangleType) {
		case arbitrary:
			// Split the triangles into top and bottom, call them as such
			slope = triangle.findSlope(1);
			b     = triangle.findB(1);

			// The new vertex for both triangles, check for right angles
			if (triangle.X[vertex1] == triangle.X[vertex3]) {
				x = triangle.X[vertex1];
			} else {
				x = (triangle.Y[vertex2] - b) / slope;	
			}

			// -------------+
			// Top triangle |
			// -------------+
			top = Triangle();
			top.triangleType = goingUp;
			topT = (triangle.Y[vertex2] - triangle.Y[vertex1]) / (triangle.Y[vertex3] - triangle.Y[vertex1]);

			// -----------------------------
			// Set the vertices up correctly
			// top triangle - vertex 1 - setup
			top.Y[0] = triangle.Y[vertex1];
			top.X[0] = triangle.X[vertex1];
			top.Z[0] = triangle.Z[vertex1];

			// top triangle - vertex 2 - setup - INTERPOLATE
			top.Y[1] = triangle.Y[vertex2];
			top.X[1] = x;
			top.Z[1] = triangle.Z[vertex1] + (topT * (triangle.Z[vertex3] - triangle.Z[vertex1]));

			// top triangle - vertex 3 - setup
			top.Y[2] = triangle.Y[vertex2];
			top.X[2] = triangle.X[vertex2];
			top.Z[2] = triangle.Z[vertex2];

			// ---------------------------
			// Set up the colors correctly
			// top triangle - vertex 1 - color
			top.colors[0][0] = triangle.colors[vertex1][0]; // red
			top.colors[0][1] = triangle.colors[vertex1][1]; // green
			top.colors[0][2] = triangle.colors[vertex1][2]; // blue

			// top triangle - vertex 2 - color - INTERPOLATE
			top.colors[1][0] = (triangle.colors[vertex1][0] + (topT * (triangle.colors[vertex3][0] - triangle.colors[vertex1][0]))); // red
			top.colors[1][1] = (triangle.colors[vertex1][1] + (topT * (triangle.colors[vertex3][1] - triangle.colors[vertex1][1]))); // green
			top.colors[1][2] = (triangle.colors[vertex1][2] + (topT * (triangle.colors[vertex3][2] - triangle.colors[vertex1][2]))); // blue

			// top triangle - vertex 3 - color
			top.colors[2][0] = triangle.colors[vertex2][0]; // red
			top.colors[2][1] = triangle.colors[vertex2][1]; // green
			top.colors[2][2] = triangle.colors[vertex2][2]; // blue

			// ----------------+
			// Bottom triangle |
			// ----------------+
			bottom = Triangle();
			bottom.triangleType = goingDown;
			bottomT = (triangle.Y[vertex2] - triangle.Y[vertex1]) / (triangle.Y[vertex3] - triangle.Y[vertex1]);

			// -----------------------------
			// Set the vertices up correctly
			// bottom triangle - vertex 1 - setup
			bottom.Y[0] = triangle.Y[vertex3];
			bottom.X[0] = triangle.X[vertex3];
			bottom.Z[0] = triangle.Z[vertex3];

			// bottom triangle - vertex 2 - setup - INTERPOLATE
			bottom.Y[1] = triangle.Y[vertex2];
			bottom.X[1] = x;
			bottom.Z[1] = triangle.Z[vertex1] + (bottomT * (triangle.Z[vertex3] - triangle.Z[vertex1]));

			// bottom triangle - vertex 3 - setup
			bottom.Y[2] = triangle.Y[vertex2];
			bottom.X[2] = triangle.X[vertex2];
			bottom.Z[2] = triangle.Z[vertex2];

			// ---------------------------
			// Set up the colors correctly
			// bottom triangle - vertex 1 - color
			bottom.colors[0][0] = triangle.colors[vertex3][0]; // red
			bottom.colors[0][1] = triangle.colors[vertex3][1]; // green
			bottom.colors[0][2] = triangle.colors[vertex3][2]; // blue

			// bottom triangle - vertex 2 - color - INTERPOLATE
			bottom.colors[1][0] = (triangle.colors[vertex1][0] + (bottomT * (triangle.colors[vertex3][0] - triangle.colors[vertex1][0]))); // red
			bottom.colors[1][1] = (triangle.colors[vertex1][1] + (bottomT * (triangle.colors[vertex3][1] - triangle.colors[vertex1][1]))); // green
			bottom.colors[1][2] = (triangle.colors[vertex1][2] + (bottomT * (triangle.colors[vertex3][2] - triangle.colors[vertex1][2]))); // blue

			// bottom triangle - vertex 3 - color
			bottom.colors[2][0] = triangle.colors[vertex2][0]; // red
			bottom.colors[2][1] = triangle.colors[vertex2][1]; // green
			bottom.colors[2][2] = triangle.colors[vertex2][2]; // blue

			// -----------------------------------+
			// Rasterize each individual triangle |
			// -----------------------------------+
			rasterizeTriangle(top, screen);
			rasterizeTriangle(bottom, screen);
			break;
		default:
			// If it's just a normal going up or going down triangle, rasterize
			// it normally
			rasterizeTriangle(triangle, screen);
			break;
	}
}

// ===================================
// Hank's Given Methods (Reading, etc)
// ===================================
std::vector<Triangle> GetTriangles(void) {
    vtkPolyDataReader *rdr = vtkPolyDataReader::New();
    rdr->SetFileName("proj1d_geometry.vtk");
    cerr << "Reading" << endl;
    rdr->Update();
    cerr << "Done reading" << endl;
    if (rdr->GetOutput()->GetNumberOfCells() == 0)
    {
        cerr << "Unable to open file!!" << endl;
        exit(EXIT_FAILURE);
    }
    vtkPolyData *pd = rdr->GetOutput();
    int numTris = pd->GetNumberOfCells();
    vtkPoints *pts = pd->GetPoints();
    vtkCellArray *cells = pd->GetPolys();
    vtkFloatArray *var = (vtkFloatArray *) pd->GetPointData()->GetArray("hardyglobal");
    float *color_ptr = var->GetPointer(0);
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
        tris[idx].Z[0] = pts->GetPoint(ptIds[0])[2];
        tris[idx].Z[1] = pts->GetPoint(ptIds[1])[2];
        tris[idx].Z[2] = pts->GetPoint(ptIds[2])[2];
        // 1->2 interpolate between light blue, dark blue
        // 2->2.5 interpolate between dark blue, cyan
        // 2.5->3 interpolate between cyan, green
        // 3->3.5 interpolate between green, yellow
        // 3.5->4 interpolate between yellow, orange
        // 4->5 interpolate between orange, brick
        // 5->6 interpolate between brick, salmon
        double mins[7] = { 1, 2, 2.5, 3, 3.5, 4, 5 };
        double maxs[7] = { 2, 2.5, 3, 3.5, 4, 5, 6 };
        unsigned char RGB[8][3] = { { 71, 71, 219 }, 
                                    { 0, 0, 91 },
                                    { 0, 255, 255 },
                                    { 0, 128, 0 },
                                    { 255, 255, 0 },
                                    { 255, 96, 0 },
                                    { 107, 0, 0 },
                                    { 224, 76, 76 } 
                                  };
        for (int j = 0 ; j < 3 ; j++)
        {
            float val = color_ptr[ptIds[j]];
            int r;
            for (r = 0 ; r < 7 ; r++)
            {
                if (mins[r] <= val && val < maxs[r])
                    break;
            }
            if (r == 7)
            {
                cerr << "Could not interpolate color for " << val << endl;
                exit(EXIT_FAILURE);
            }
            double proportion = (val-mins[r]) / (maxs[r]-mins[r]);
            tris[idx].colors[j][0] = (RGB[r][0]+proportion*(RGB[r+1][0]-RGB[r][0]))/255.0;
            tris[idx].colors[j][1] = (RGB[r][1]+proportion*(RGB[r+1][1]-RGB[r][1]))/255.0;
            tris[idx].colors[j][2] = (RGB[r][2]+proportion*(RGB[r+1][2]-RGB[r][2]))/255.0;
        }
    }

    return tris;
}

// +-------------+
// | *********** |
// | Main Method |
// | *********** |
// +-------------+

int main(int argc, char *argv[]) {
	vtkImageData *image   = NewImage(1000, 1000);
	unsigned char *buffer = (unsigned char *) image->GetScalarPointer(0,0,0);

	int npixels = 1000*1000;

	int i;
	// Black out the buffer
	for (i = 0 ; i < npixels*3 ; i++) {
	   buffer[i] = 0;
	}

	// Initialize the zBuffer
	double zBuffer[npixels];
	for (i = 0; i < npixels; ++i) {
		zBuffer[i] = -1.0;
	}

	std::vector<Triangle> triangles = GetTriangles();

	Screen screen;
	screen.buffer  = buffer;
	screen.zBuffer = zBuffer;
	screen.width   = 1000;
	screen.height  = 1000;

	// Draw the triangles!
	for (auto triangle : triangles) {
		drawTriangle(triangle, screen);
	}

	WriteImage(image, "allTriangles");
}
