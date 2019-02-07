#include <math.h>
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
#include <vtkDoubleArray.h>

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

double cotan(double num) {
	return (1 / tan(num));
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

// +----------------------------+
// | ************************** |
// | Matrix Class & Its Methods |
// | ************************** |
// +----------------------------+

class Matrix {
  public:
	double A[4][4];  // A[i][j] means row i, column j

	void Print(ostream &o);
	void TransformPoint(const double *ptIn, double *ptOut);
	static Matrix ComposeMatrices(const Matrix &, const Matrix &);
};

void Matrix::Print(ostream &o) {
	for (int i = 0 ; i < 4 ; i++) {
		char str[256];
		sprintf(str, "(%.7f %.7f %.7f %.7f)\n", A[i][0], A[i][1], A[i][2], A[i][3]);
		o << str;
	}
}

Matrix Matrix::ComposeMatrices(const Matrix &M1, const Matrix &M2) {
	Matrix rv;
	for (int i = 0 ; i < 4 ; i++) {
		for (int j = 0 ; j < 4 ; j++) {
			rv.A[i][j] = 0;
			for (int k = 0 ; k < 4 ; k++) {
				rv.A[i][j] += M1.A[i][k]*M2.A[k][j];
			}
		}
	}

	return rv;
}

void Matrix::TransformPoint(const double *ptIn, double *ptOut) {
	ptOut[0] = ptIn[0]*A[0][0]
			 + ptIn[1]*A[1][0]
			 + ptIn[2]*A[2][0]
			 + ptIn[3]*A[3][0];
	ptOut[1] = ptIn[0]*A[0][1]
			 + ptIn[1]*A[1][1]
			 + ptIn[2]*A[2][1]
			 + ptIn[3]*A[3][1];
	ptOut[2] = ptIn[0]*A[0][2]
			 + ptIn[1]*A[1][2]
			 + ptIn[2]*A[2][2]
			 + ptIn[3]*A[3][2];
	ptOut[3] = ptIn[0]*A[0][3]
			 + ptIn[1]*A[1][3]
			 + ptIn[2]*A[2][3]
			 + ptIn[3]*A[3][3];
}

// +----------------------------+
// | ************************** |
// | Camera Class & Its Methods |
// | ************************** |
// +----------------------------+

class Camera {
 public:
	double near, far;
	double angle;
	double position[3];
	double focus[3];
	double up[3];

	Matrix ViewTransform(void);
	Matrix CameraTransform(void);
	Matrix DeviceTransform(int width, int height);
};

double dot_product(double *a, double *b) {
	double result = 0.0;

	int i;
	for (i = 0; i<3; ++i) {
		result += a[i] * b[i];
	}

	return result;
}

Matrix Camera::DeviceTransform(int width, int height) {
	// Cast the width and height to doubles
	width  = double (width);
	height = double (height);

	Matrix matrix;	

	// Row 1
	matrix.A[0][0] = width / 2.0;
	matrix.A[0][1] = 0.0;
	matrix.A[0][2] = 0.0;
	matrix.A[0][3] = 0.0;

	// Row 2
	matrix.A[1][0] = 0.0;
	matrix.A[1][1] = height / 2.0;
	matrix.A[1][2] = 0.0;
	matrix.A[1][3] = 0.0;

	// Row 3
	matrix.A[2][0] = 0.0;
	matrix.A[2][1] = 0.0;
	matrix.A[2][2] = 1.0;
	matrix.A[2][3] = 0.0;

	// Row 4
	matrix.A[3][0] = width / 2.0;
	matrix.A[3][1] = height / 2.0;
	matrix.A[3][2] = 0.0;
	matrix.A[3][3] = 1.0;

	return matrix;
}

Matrix Camera::ViewTransform() {
	Matrix matrix;	

	// Row 1
	matrix.A[0][0] = cotan(this->angle / 2.0);
	matrix.A[0][1] = 0.0;
	matrix.A[0][2] = 0.0;
	matrix.A[0][3] = 0.0;

	// Row 2
	matrix.A[1][0] = 0.0;
	matrix.A[1][1] = cotan(this->angle / 2.0);
	matrix.A[1][2] = 0.0;
	matrix.A[1][3] = 0.0;

	// Row 3
	matrix.A[2][0] = 0.0;
	matrix.A[2][1] = 0.0;
	matrix.A[2][2] = (this->far + this->near) / (this->far - this->near);
	matrix.A[2][3] = -1.0;

	// Row 4
	matrix.A[3][0] = 0.0;
	matrix.A[3][1] = 0.0;
	matrix.A[3][2] = (2.0 * (this->far * this->near)) / (this->far - this->near);
	matrix.A[3][3] = 0.0;

	return matrix;
}

Matrix Camera::CameraTransform() {
	int i;
	double origin[3];
	for (i=0;i<3;++i) { origin[i] = this->position[i]; }

	// w vector, which is used by u (so I declare it first)
	double w[3]  = { (origin[0] - focus[0]),
					 (origin[1] - focus[1]),
					 (origin[2] - focus[2]) };
	double normW = sqrt(w[0]*w[0] + w[1]*w[1] + w[2]*w[2]);
	for (i=0;i<3;++i) { w[i] /= normW; }

	// u vector, which is used by v (so I declare it second)
	double u[3]  = { (this->up[1] * w[2]) - (this->up[2] * w[1]), 
					 (this->up[2] * w[0]) - (this->up[0] * w[2]),
					 (this->up[0] * w[1]) - (this->up[1] * w[0]) };
	double normU = sqrt(u[0]*u[0] + u[1]*u[1] + u[2]*u[2]);
	for (i=0;i<3;++i) { u[i] /= normU; }

	// v vector
	double v[3]  = { (w[1] * u[2]) - (w[2] * u[1]), 
					 (w[2] * u[0]) - (w[0] * u[2]),
					 (w[0] * u[1]) - (w[1] * u[0]) };
	double normV = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	for (i=0;i<3;++i) { v[i] /= normV; }

	// t vector
	double t[3] = { 0.0 - origin[0],
					0.0 - origin[1],
					0.0 - origin[2] };

	Matrix matrix;	

	// Row 1
	matrix.A[0][0] = u[0];
	matrix.A[0][1] = v[0];
	matrix.A[0][2] = w[0];
	matrix.A[0][3] = 0.0;

	// Row 2
	matrix.A[1][0] = u[1];
	matrix.A[1][1] = v[1];
	matrix.A[1][2] = w[1];
	matrix.A[1][3] = 0.0;

	// Row 3
	matrix.A[2][0] = u[2];
	matrix.A[2][1] = v[2];
	matrix.A[2][2] = w[2];
	matrix.A[2][3] = 0.0;

	// Row 4
	matrix.A[3][0] = dot_product(u, t);
	matrix.A[3][1] = dot_product(v, t);
	matrix.A[3][2] = dot_product(w, t);
	matrix.A[3][3] = 1.0;

	return matrix;
}

double SineParameterize(int curFrame, int nFrames, int ramp) {
	int nNonRamp = nFrames-2*ramp;
	double height = 1./(nNonRamp + 4*ramp/M_PI);
	if (curFrame < ramp) {
		double factor = 2*height*ramp/M_PI;
		double eval = cos(M_PI/2*((double)curFrame)/ramp);
		return (1.-eval)*factor;
	}
	else if (curFrame > nFrames-ramp) {
		int amount_left = nFrames-curFrame;
		double factor = 2*height*ramp/M_PI;
		double eval =cos(M_PI/2*((double)amount_left/ramp));
		return 1. - (1-eval)*factor;
	}
	double amount_in_quad = ((double)curFrame-ramp);
	double quad_part = amount_in_quad*height;
	double curve_part = height*(2*ramp)/M_PI;
	return quad_part+curve_part;
}

Camera GetCamera(int frame, int nframes) {
	double t = SineParameterize(frame, nframes, nframes/10);
	Camera c;
	c.near = 5;
	c.far = 200;
	c.angle = M_PI/6;
	c.position[0] = 40*sin(2*M_PI*t);
	c.position[1] = 40*cos(2*M_PI*t);
	c.position[2] = 40;
	c.focus[0] = 0;
	c.focus[1] = 0;
	c.focus[2] = 0;
	c.up[0] = 0;
	c.up[1] = 1;
	c.up[2] = 0;
	return c;
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

	Screen(int height, int width, unsigned char *buffer);

	void InitializeScreen();

	void ImageColor(int row, int column, double z, double color[3]);
};

Screen::Screen(int height, int width, unsigned char *buffer) {
	this->buffer = buffer;
	this->width  = width;
	this->height = height;

	int npixels = width * height;
	int i;

	// Black out the buffer
	for (i = 0; i < npixels*3; i++) {
	   buffer[i] = 0;
	}
	this->buffer = buffer;

	// Initialize the zBuffer
	double zBuffer[npixels];
	for (i = 0; i < npixels; ++i) {
		zBuffer[i] = -1.0;
	}
	this->zBuffer = zBuffer;
}

void Screen::InitializeScreen() {
	int npixels = this->width * this->height;

	int i;
	// Reset the buffer
	for (i = 0; i < npixels*3; i++) {
	   this->buffer[i] = 0;
	}

	// Reset the zBuffer
	double zBuffer[npixels];
	for (i = 0; i < npixels; ++i) {
		zBuffer[i] = -1.0;
	}
	this->zBuffer = zBuffer;
}

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
	//cout << "done printing" << endl;
}

void transformToDevSpace(Triangle triangle, Screen screen, Camera camera) {
	// The triangles original vertices, save them to reset after drawing
	double originalX[3];
	double originalY[3];
	double originalZ[3];

	int i;
	for (i=0; i<3; ++i) {
		originalX[i] = triangle.X[i];
		originalY[i] = triangle.Y[i];
		originalZ[i] = triangle.Z[i];
	}

	// The three transformation matrices
	Matrix cameraMatrix = camera.CameraTransform();
	Matrix viewMatrix   = camera.ViewTransform();
	Matrix devMatrix    = camera.DeviceTransform(screen.width, screen.height);

	Matrix intermediateMatrix = cameraMatrix.ComposeMatrices(cameraMatrix, viewMatrix);
	Matrix finalMatrix        = intermediateMatrix.ComposeMatrices(intermediateMatrix, devMatrix);

	// The input points are the input triangle's + the "w" component,
	// output points are empty for now
	double xInPoint[4] = { triangle.X[0],
						   triangle.Y[0],
						   triangle.Z[0], 
						   1.0 };
	double yInPoint[4] = { triangle.X[1],
						   triangle.Y[1],
						   triangle.Z[1], 
						   1.0 };
	double zInPoint[4] = { triangle.X[2],
						   triangle.Y[2],
						   triangle.Z[2], 
						   1.0 };
	double xOutPoint[4], yOutPoint[4], zOutPoint[4];

	// Transform the points with the final matrix
	finalMatrix.TransformPoint(xInPoint, xOutPoint);
	finalMatrix.TransformPoint(yInPoint, yOutPoint);
	finalMatrix.TransformPoint(zInPoint, zOutPoint);

	// Make sure we don't divide by 0
	for (i=0; i<3; ++i) {
		(xOutPoint[3] != 0) ? xOutPoint[i] /= xOutPoint[3] : i+0 ;
		(yOutPoint[3] != 0) ? yOutPoint[i] /= yOutPoint[3] : i+0 ;
		(zOutPoint[3] != 0) ? zOutPoint[i] /= zOutPoint[3] : i+0 ;
	}

	// New triangle vertices
	triangle.X[0] = xOutPoint[0]; triangle.X[1] = yOutPoint[0]; triangle.X[2] = zOutPoint[0];
	triangle.Y[0] = xOutPoint[1]; triangle.Y[1] = yOutPoint[1]; triangle.Y[2] = zOutPoint[1];
	triangle.Z[0] = xOutPoint[2]; triangle.Z[1] = yOutPoint[2]; triangle.Z[2] = zOutPoint[2];

	drawTriangle(triangle, screen);

	// Reset the triangle
	triangle.X[0] = originalX[0]; triangle.X[1] = originalX[1]; triangle.X[2] = originalX[2];
	triangle.Y[0] = originalY[0]; triangle.Y[1] = originalY[1]; triangle.Y[2] = originalY[2];
	triangle.Z[0] = originalZ[0]; triangle.Z[1] = originalZ[1]; triangle.Z[2] = originalZ[2];
}

// ===================================
// Hank's Given Methods (Reading, etc)
// ===================================
std::vector<Triangle> GetTriangles(void) {
	vtkPolyDataReader *rdr = vtkPolyDataReader::New();
	rdr->SetFileName("proj1e_geometry.vtk");
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
	vtkDoubleArray *var = (vtkDoubleArray *) pd->GetPointData()->GetArray("hardyglobal");
	double *color_ptr = var->GetPointer(0);
	//vtkFloatArray *var = (vtkFloatArray *) pd->GetPointData()->GetArray("hardyglobal");
	//float *color_ptr = var->GetPointer(0);
	vtkFloatArray *n = (vtkFloatArray *) pd->GetPointData()->GetNormals();
	float *normals = n->GetPointer(0);
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
		double *pt = NULL;
		pt = pts->GetPoint(ptIds[0]);
		tris[idx].X[0] = pt[0];
		tris[idx].Y[0] = pt[1];
		tris[idx].Z[0] = pt[2];
	#ifdef NORMALS
		tris[idx].normals[0][0] = normals[3*ptIds[0]+0];
		tris[idx].normals[0][1] = normals[3*ptIds[0]+1];
		tris[idx].normals[0][2] = normals[3*ptIds[0]+2];
	#endif
		pt = pts->GetPoint(ptIds[1]);
		tris[idx].X[1] = pt[0];
		tris[idx].Y[1] = pt[1];
		tris[idx].Z[1] = pt[2];
	#ifdef NORMALS
		tris[idx].normals[1][0] = normals[3*ptIds[1]+0];
		tris[idx].normals[1][1] = normals[3*ptIds[1]+1];
		tris[idx].normals[1][2] = normals[3*ptIds[1]+2];
	#endif
		pt = pts->GetPoint(ptIds[2]);
		tris[idx].X[2] = pt[0];
		tris[idx].Y[2] = pt[1];
		tris[idx].Z[2] = pt[2];
	#ifdef NORMALS
		tris[idx].normals[2][0] = normals[3*ptIds[2]+0];
		tris[idx].normals[2][1] = normals[3*ptIds[2]+1];
		tris[idx].normals[2][2] = normals[3*ptIds[2]+2];
	#endif

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

	std::vector<Triangle> triangles = GetTriangles();

	Screen screen = Screen(1000, 1000, buffer);

	int i;
	for (i=0; i<1000; i+=250) {
		// Initialize the camera position as well as initialize the screen
		// to be blacked out, zbuffer reset
		screen.InitializeScreen();
		Camera camera = GetCamera(i, 1000);

		// Draw the triangles!
		for (auto triangle : triangles) {
			transformToDevSpace(triangle, screen, camera);
		}

		// Set up filename and write the file out
		char fileBuffer[50];
		sprintf(fileBuffer, "frame%03d", i);
		WriteImage(image, fileBuffer);
	}
}
