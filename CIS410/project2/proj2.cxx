/*=========================================================================

  Program:   Visualization Toolkit
  Module:    SpecularSpheres.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

	 This software is distributed WITHOUT ANY WARRANTY; without even
	 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
	 PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
//
// This examples demonstrates the effect of specular lighting.
//
#include "vtkSmartPointer.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkInteractorStyle.h"
#include "vtkObjectFactory.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkLight.h"
#include "vtkOpenGLPolyDataMapper.h"
#include "vtkJPEGReader.h"
#include "vtkImageData.h"

#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>
#include <vtkDataSetReader.h>
#include <vtkContourFilter.h>
#include <vtkRectilinearGrid.h>
#include <vtkFloatArray.h>


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
	//return idx[2]*(dims[0]-1)*(dims[1]-1)+idx[1]*(dims[0]-1)*idx[0];
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

// Thanks to my brother for helping me set up this method, reduces a LOT of boilerplate
void SetupFieldValues(const int idx, const int *dims, const float *F, float *fieldValues)
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

					// Equations taken from helper He He in Piazza post @34 (or slides)
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

					// Can't just straight up return this equation... no idea why. Makes it
					// output random numbers.
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

// ****************************************************************************
//  Function: BoundingBoxForCell
//
//  Arguments:
//     X: an array (size is specified by dims).
//              This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).
//              This contains the Y locations of a rectilinear mesh.
//     dims: an array of size two.
//              The first number is the size of the array in argument X,
//              the second the size of Y.
//     cellId: a cellIndex (I.e., between 0 and GetNumberOfCells(dims))
//     bbox (output): the bounding box of cellId.  Format should be
//                     bbox[0]: the minimum X value in cellId.
//                     bbox[1]: the maximum X value in cellId.
//                     bbox[2]: the minimum Y value in cellId.
//                     bbox[3]: the maximum Y value in cellId.
//
//  Returns:  None (argument bbox is output)
//
// ****************************************************************************

void BoundingBoxForCell(const float *X, const float *Y, const int *dims,
				   int cellId, float *bbox)
{
	bbox[0] = -100;
	bbox[1] = +100;
	bbox[2] = -100;
	bbox[3] = +100;
	int logicalCellIndex[2];

	// Handling "invalid arguments" as per prompt
	if (cellId >= GetNumberOfCells(dims))
	{
		return;
	}
	else
	{
		GetLogicalCellIndex(logicalCellIndex, cellId, dims);
		bbox[0] = X[logicalCellIndex[0]];
		bbox[1] = X[logicalCellIndex[0] + 1];
		bbox[2] = Y[logicalCellIndex[1]];
		bbox[3] = Y[logicalCellIndex[1] + 1];
	}
}

// ****************************************************************************
//  Function: CountNumberOfStraddingCells
//
//  Arguments:
//     X: an array (size is specified by dims).
//              This contains the X locations of a rectilinear mesh.
//     Y: an array (size is specified by dims).
//              This contains the Y locations of a rectilinear mesh.
//     dims: an array of size two.
//              The first number is the size of the array in argument X,
//              the second the size of Y.
//     F: a scalar field defined on the mesh.  Its size is dims[0]*dims[1].
//
//  Returns:  the number of cells that straddle 0, i.e., the number of cells
//            that contains points who have F>0 and also have points with F<0.
//
// ****************************************************************************

int CountNumberOfStraddlingCells(const float *X, const float *Y, const int *dims,
							 const float *F)
{
	int i, j;
	int count = 0;
	int cellCount = GetNumberOfCells(dims);
	bool foundPositive, foundNegative;

	for (i=0; i<cellCount; ++i)
	{
		// For some reason having this defined outside of the loop
		// makes count be 41 instead of 40??? I don't know why, even
		// when I use std::fill_n to reset the array it's still counting
		// too high... I don't like declaring variables in loops
		float fieldValues[4];
		SetupFieldValues(i, dims, F, fieldValues);

		for (j=0; j<4; ++j)
		{
			if (fieldValues[j] > 0)
				foundPositive = true;
			else
				foundNegative = true;
		}

		if (foundNegative && foundPositive)
			count++;

		foundPositive = false; foundNegative = false;
	}

	return count;
}

int main()
{
	int  i;

	vtkDataSetReader *rdr = vtkDataSetReader::New();
	rdr->SetFileName("proj2_data.vtk");
	rdr->Update();

	int dims[3];
	vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
	rgrid->GetDimensions(dims);

	float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
	float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
	float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);

	int numCells = CountNumberOfStraddlingCells(X, Y, dims, F);
	cerr << "The number of cells straddling zero is " << numCells << endl;

	float bbox[4];
	const int ncells = 5;
	int cellIds[ncells] = { 0, 50, 678, 1000, 1200 };
	for (i = 0 ; i < ncells ; i++)
	{
		BoundingBoxForCell(X, Y, dims, cellIds[i], bbox);
		cerr << "The bounding box for cell " << cellIds[i] << " is "
			 << bbox[0] << "->" << bbox[1] << ", " << bbox[2] << "->" << bbox[3]
			 << endl;
	}

	const int npts = 10;
	float pt[npts][3] =
		 {
			{1.01119, 0.122062, 0},
			{0.862376, 1.33839, 0},
			{0.155026, 0.126123, 0},
			{0.69736, 0.0653565, 0},
			{0.2, 0.274117, 0},
			{0.893699, 1.04111, 0},
			{0.608791, -0.0533753, 0},
			{1.00543, 0.138024, 0},
			{0.384128, -0.0768977, 0},
			{0.666757, 0.60259, 0},
		 };



	for (i = 0 ; i < npts ; i++)
	{
		float f = EvaluateFieldAtLocation(pt[i], dims, X, Y, F);
		cerr << "Evaluated field at (" << pt[i][0] <<"," << pt[i][1] << ") as "
			 << f << endl;
	}
}
