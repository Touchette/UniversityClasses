#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDataSetReader.h>
#include <vtkRectilinearGrid.h>
#include <vtkFloatArray.h>
#include <math.h>

// ****************************************************************************
//  Function: GetNumberOfPoints
//
//  Arguments:
//     dims: an array of size 3 with the number of points in X, Y, and Z.
//           2D data sets would have Z=1
//
//  Returns:  the number of points in a rectilinear mesh
//
// ****************************************************************************

int GetNumberOfPoints(const int *dims)
{
    // 3D
    //return dims[0]*dims[1]*dims[2];
    // 2D
    return dims[0]*dims[1];
}

// ****************************************************************************
//  Function: GetNumberOfCells
//
//  Arguments:
//
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the number of cells in a rectilinear mesh
//
// ****************************************************************************

int GetNumberOfCells(const int *dims)
{
    // 3D
    //return (dims[0]-1)*(dims[1]-1)*(dims[2]-1);
    // 2D
    return (dims[0]-1)*(dims[1]-1);
}


// ****************************************************************************
//  Function: GetPointIndex
//
//  Arguments:
//      idx:  the logical index of a point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1]
//              2 <= idx[2] < dims[2] (or always 0 if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the point index
//
// ****************************************************************************

int GetPointIndex(const int *idx, const int *dims)
{
    // 3D
    //return idx[2]*dims[0]*dims[1]+idx[1]*dims[0]+idx[0];
    // 2D
    return idx[1]*dims[0]+idx[0];
}


// ****************************************************************************
//  Function: GetCellIndex
//
//  Arguments:
//      idx:  the logical index of a cell.
//              0 <= idx[0] < dims[0]-1
//              1 <= idx[1] < dims[1]-1
//              2 <= idx[2] < dims[2]-1 (or always 0 if 2D)
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  the cell index
//
// ****************************************************************************

int GetCellIndex(const int *idx, const int *dims)
{
    // 3D
    //return idx[2]*(dims[0]-1)*(dims[1]-1)+idx[1]*(dims[0]-1)+idx[0];
    // 2D
    return idx[1]*(dims[0]-1)+idx[0];
}

// ****************************************************************************
//  Function: GetLogicalPointIndex
//
//  Arguments:
//      idx (output):  the logical index of the point.
//              0 <= idx[0] < dims[0]
//              1 <= idx[1] < dims[1]
//              2 <= idx[2] < dims[2] (or always 0 if 2D)
//      pointId:  a number between 0 and (GetNumberOfPoints(dims)-1).
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  None (argument idx is output)
//
// ****************************************************************************

void GetLogicalPointIndex(int *idx, int pointId, const int *dims)
{
    // 3D
    // idx[0] = pointId%dim[0];
    // idx[1] = (pointId/dims[0])%dims[1];
    // idx[2] = pointId/(dims[0]*dims[1]);

    // 2D
    idx[0] = pointId%dims[0];
    idx[1] = pointId/dims[0];
}


// ****************************************************************************
//  Function: GetLogicalCellIndex
//
//  Arguments:
//      idx (output):  the logical index of the cell index.
//              0 <= idx[0] < dims[0]-1
//              1 <= idx[1] < dims[1]-1
//              2 <= idx[2] < dims[2]-1 (or always 0 if 2D)
//      cellId:  a number between 0 and (GetNumberOfCells(dims)-1).
//      dims: an array of size 3 with the number of points in X, Y, and Z.
//            2D data sets would have Z=1
//
//  Returns:  None (argument idx is output)
//
// ****************************************************************************

void GetLogicalCellIndex(int *idx, int cellId, const int *dims)
{
    // 3D
    // idx[0] = cellId%(dims[0]-1);
    // idx[1] = (cellId/(dims[0]-1))%(dims[1]-1);
    // idx[2] = cellId/((dims[0]-1)*(dims[1]-1));

    // 2D
    idx[0] = cellId%(dims[0]-1);
    idx[1] = cellId/(dims[0]-1);
}

// ****************************************************************************
//  Function: EvaluateFieldAtLocation
//
//  Arguments:
//     pt: a two-dimensional location
//     dims: an array of size two.
//              The first number is the size of the array in argument X,
//              the second the size of Y.
//     X: an array (size is specified by dims).
//              This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).
//              This contains the Y locations of a rectilinear mesh.
//     F: a scalar field defined on the mesh.  Its size is dims[0]*dims[1].
//
//   Returns: the interpolated field value. 0 if the location is out of bounds.
//
// ****************************************************************************

// Thanks to my brother for helping me set up this method, reduces a LOT of
// boilerplate
void SetupFieldValues(const int idx, const int *dims, const float *F,
                float *fieldValues)
{
	int bottomLeftIndex[2]; GetLogicalCellIndex(bottomLeftIndex, idx, dims);
	int topLeftIndex[2]     = { bottomLeftIndex[0], bottomLeftIndex[1] + 1 };
	int bottomRightIndex[2] = { bottomLeftIndex[0] + 1, bottomLeftIndex[1] };
	int topRightIndex[2]    = { bottomLeftIndex[0] + 1, bottomLeftIndex[1] + 1 };

	fieldValues[0] = F[GetPointIndex(bottomLeftIndex, dims)];
	fieldValues[1] = F[GetPointIndex(topLeftIndex, dims)];
	fieldValues[2] = F[GetPointIndex(bottomRightIndex, dims)];
	fieldValues[3] = F[GetPointIndex(topRightIndex, dims)];
}

float EvaluateFieldAtLocation(const float *pt, const int *dims,
						const float *X, const float *Y, const float *F)
{
	int i, j;
	int cellIndex;
	float t, bottom, top, lerpedValue = 0.f;
	float fieldValues[4];

	// Iterate over X, then over Y, as per Piazza answer on post @41
	// Find logical X component
	for (i=0; i<dims[0]; ++i)
	{
		if (X[i] <= pt[0] && X[i+1] >= pt[0])
		{
			// Find logical Y component
			for (j=0; j<dims[1]; ++j)
			{
				if (Y[j] <= pt[1] && Y[j+1] >= pt[1])
				{
					// Lerp setup
					int logicalCellIndex[2] = {i, j};
					cellIndex = GetCellIndex(logicalCellIndex, dims);
					SetupFieldValues(cellIndex, dims, F, fieldValues);

					// Equations taken from helper He He in Piazza post @34 (or
                    // slides)
					// +--------------------------+
					// | Horizontal interpolation |
					// +--------------------------+
					// t:
					//	(u.x - A.x) / (B.x - A.x)
					t = (pt[0] - X[i]) / (X[i+1] - X[i]);

					// F(bottom):
					//	F(C) + t (F(D) - F(C))
					bottom = fieldValues[0] + t * (fieldValues[2] - fieldValues[0]);

					// F(top):
					//	F(A) + t * (F(B) - F(A))
					top    = fieldValues[1] + t * (fieldValues[3] - fieldValues[1]);

					// +------------------------+
					// | Vertical interpolation |
					// +------------------------+
					// t:
					//	(u.y - A.y) / (B.y - A.y)
					t = (pt[1] - Y[j]) / (Y[j+1] - Y[j]);

					// Can't just straight up return this equation... no idea
                    // why. Makes it output random numbers.
					// Lerped value:
					//	F(x) = F(bottom) + t * (F(bottom) - F(top))
					lerpedValue = bottom + t * (top - bottom);
					break;
				}
			}
		}
	}

	return lerpedValue;
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

vtkImageData *
NewImage(int width, int height)
{
    vtkImageData *image = vtkImageData::New();
    image->SetDimensions(width, height, 1);
    //image->SetWholeExtent(0, width-1, 0, height-1, 0, 0);
    //image->SetUpdateExtent(0, width-1, 0, height-1, 0, 0);
    //image->SetNumberOfScalarComponents(3);
    image->AllocateScalars(VTK_UNSIGNED_CHAR, 3);
    //image->AllocateScalars();

    return image;
}

// ****************************************************************************
//  Function: ApplyBlueHotColorMap
//
//  Purpose:
//     Maps a normalized scalar value F (0<=F<=1) to a color using the blue
//     hot color map.
//
//     The blue hot color map has:
//        F=0: (0,0,128)
//        F=1: (255,255,255)
//       and smooth interpolation in between
//
//  Arguments:
//       F (input):     a scalar value between 0 and 1
//       RGB (output):  the location to store the color
//
// ****************************************************************************

void ApplyBlueHotColorMap(float F, unsigned char *RGB)
{
    RGB[0] = F * 255;
    RGB[1] = F * 255;
    RGB[2] = 128 + (F * 127); // 255 - 128 = 127
}


// ****************************************************************************
//  Function: ApplyDifferenceColorMap
//
//  Purpose:
//     Maps a normalized scalar value F (0<=F<=1) to a color using a divergent
//     colormap
//
//     The divergent color map has:
//        F=0: (0,0,128)
//        F=0.5: (255,255,255)
//        F=1: (128, 0, 0)
//       and smooth interpolation in between
//
//  Arguments:
//       F (input):     a scalar value between 0 and 1
//       RGB (output):  the location to store the color
//
// ****************************************************************************
void ApplyDifferenceColorMap(float F, unsigned char *RGB)
{
    float lower_t = (F - 0.f) / (0.5f - 0.f);
    float upper_t = (F - 0.5f) / (1.f - 0.5f);

    if (F < 0.5)
    {
        RGB[0] = 0   + lower_t * (255 - 0);
        RGB[1] = 0   + lower_t * (255 - 0);
        RGB[2] = 128 + lower_t * (255 - 128);
    }
    if (F == 0.5)
    {
        RGB[0] = 255;
        RGB[1] = 255;
        RGB[2] = 255;
    }
    if (F > 0.5)
    {
        RGB[0] = 255 + upper_t * (128 - 255);
        RGB[1] = 255 + upper_t * (0 - 255);
        RGB[2] = 255 + upper_t * (0 - 255);
    }
}

// ****************************************************************************
//  Function: ApplyBHSVColorMap
//
//  Purpose:
//     Maps a normalized scalar value F (0<=F<=1) to a color using an HSV
//     rainbow colormap
//
//     The rainbow colormap uses a saturation = 1.0, value = 1.0,
//     and interpolates hue from 0 to 360 degrees
//
//  Arguments:
//       F (input):     a scalar value between 0 and 1
//       RGB (output):  the location to store the color
//
// ****************************************************************************
void ApplyHSVColorMap(float F, unsigned char *RGB)
{
    float saturation = 1.f;
    float value      = 1.f;
    // Math from same StackOverflow post #5731863 (Alok Singhal)
    float hue = (0.f + ((360.f - 0.f) / (1.f - 0.f)) * (F - 0.f)) / 60.f;
    int i = floor(hue);
    float f = hue - i;
    float p = value * (1 - saturation);
    float q = value * (1 - saturation * f);
    float t = value * (1 - saturation * (1 - f));
    p *= 255; q *= 255; t *= 255;
    saturation *= 255; value *= 255;
    switch (i)
    {
        case 0:
            RGB[0] = value; RGB[1] = t; RGB[2] = p;
            break;
        case 1:
            RGB[0] = q; RGB[1] = value; RGB[2] = p;
            break;
        case 2:
            RGB[0] = p; RGB[1] = value; RGB[2] = t;
            break;
        case 3:
            RGB[0] = p; RGB[1] = q; RGB[2] = value;
            break;
        case 4:
            RGB[0] = t; RGB[1] = p; RGB[2] = value;
            break;
        case 5:
            RGB[0] = value; RGB[1] = p; RGB[2] = q;
            break;
    }
}


int main()
{
    int  i, j;

    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj3_data.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);

    int nx = 500;
    int ny = 500;

    vtkImageData *images[3];
    unsigned char *buffer[3];
    for (i = 0 ; i < 3 ; i++)
    {
        images[i] = NewImage(nx, ny);
        buffer[i] = (unsigned char *) images[i]->GetScalarPointer(0,0,0);
    }

    for (i = 0 ; i < 3*nx*ny ; i++)
        for (j = 0 ; j < 3 ; j++)
            buffer[j][i] = 0;

    // Math from StackOverflow question #5731863 (Alok Singhal)
    float slopeX = (9.f - -9.f) / ((nx - 1) - 0.f);
    float slopeY = (9.f - -9.f) / ((ny - 1) - 0.f);
    for (i=0; i<nx; i++)
        for (j=0; j<ny; j++)
        {
            // ITERATE OVER PIXELS
            float pt[2];
            pt[0] = -9.f + (slopeX * (i - 0.f));
            pt[1] = -9.f + (slopeY * (j - 0.f));

            float f = EvaluateFieldAtLocation(pt, dims, X, Y, F);
            float normalizedF = (f - 1.2f) / (5.02f - 1.2f);

            // I TAKE OVER HERE
            int offset = 3*(j*nx+i);
            ApplyBlueHotColorMap(normalizedF, buffer[0]+offset);
            ApplyDifferenceColorMap(normalizedF, buffer[1]+offset);
            ApplyHSVColorMap(normalizedF, buffer[2]+offset);
        }

    WriteImage(images[0], "bluehot_output");
    WriteImage(images[1], "difference_output");
    WriteImage(images[2], "hsv_output");
}
