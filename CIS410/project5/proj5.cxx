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
#include <vtkPNGWriter.h>

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

#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>


// Lookup table from Lecture 7, pre-computation of all cases
int lup[16][4] =
{
    { -1, -1, -1, -1 }, // Case 0
    {  0,  3, -1, -1 }, // Case 1
    {  0,  1, -1, -1 }, // Case 2
    {  1,  3, -1, -1 }, // Case 3
    {  2,  3, -1, -1 }, // Case 4
    {  0,  2, -1, -1 }, // Case 5
    {  0,  1,  2,  3 }, // Case 6
    {  1,  2, -1, -1 }, // Case 7
    {  1,  2, -1, -1 }, // Case 8
    {  0,  3,  1,  2 }, // Case 9
    {  0,  2, -1, -1 }, // Case 10
    {  2,  3, -1, -1 }, // Case 11
    {  1,  3, -1, -1 }, // Case 12
    {  0,  1, -1, -1 }, // Case 13
    {  0,  3, -1, -1 }, // Case 14
    { -1, -1, -1, -1 }  // Case 15
};

// Number of line segments for each case in lup
int numSegments[16] =
{
    0, // Case 0
    1, // Case 1
    1, // Case 2
    1, // Case 3
    1, // Case 4
    1, // Case 5
    2, // Case 6
    1, // Case 7
    1, // Case 8
    2, // Case 9
    1, // Case 10
    1, // Case 11
    1, // Case 12
    1, // Case 13
    1, // Case 14
    0  // Case 15
};


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
//  Function: IdentifyCase
//
//  Arguments:
//      A, B, C, D: floats which correspond to the vertices of the cell we are
//                  identifying
//
//  Returns:  Index into the global lookup table, "lup"
//
// ****************************************************************************

int IdentifyCase(float A, float B, float C, float D)
{
    float isovalue = 3.2; // the magical isovalue of 3.2

    int builtBinary = ((A > isovalue) ? 1 : 0) +
                      ((B > isovalue) ? 2 : 0) +
                      ((C > isovalue) ? 4 : 0) +
                      ((D > isovalue) ? 8 : 0);

    return builtBinary;
}


// ****************************************************************************
//  Function: InterpolateIsoline
//
//  Arguments:
//      edge: which edge of the cell we are LERPing on, also which edge the
//            isoline's point is lying upon
//      A, B, C, D: floats which correspond to the vertices of the cell we are
//                  identifying
//      pos0, pos1, pos2, pos3: the X and Y coords of the positions of each
//                              of the vertices A, B, C, and D respectively
//      pt: the output array that will be written via AddSegment
//
//  Returns:  None (argument pt is output)
//
// ****************************************************************************

void InterpolateIsoline(int edge,
                        float A, float B, float C, float D,
                        float *pos0, float *pos1, float *pos2, float *pos3,
                        float *pt)
{
    float isovalue = 3.2; // the magical isovalue of 3.2
    float t;

    // Horrible ASCII drawing of case 14 using slides 36 and 47 for reference:
    //                  edge2
    //        C --------------------- D
    //        |                       |
    //        |\ <- isovalue_y        |
    //        | \                     |
    //        |  \                    |
    // edge3  |   \                   | edge1
    //        |    \                  |
    //        |     \                 |
    //        |      \ <- isovalue_x  |
    //        A --------------------- B
    //                  edge0
    // Example for isovalue_x, this would be case 0 for edge 0:
    //     t     = (isovalue_x - A) / (B - A)
    //     pt[0] = A_x + t * (B_x - A_x);
    //     pt[1] = A_y; (could also be B_y, tbh)
    // (Works out just like the formula! I can derive all cases from this)
    switch (edge)
    {
        // Case 0 is the bottom of the cell (edge 0)
        case 0:
            t     = (isovalue - A) / (B - A);
            pt[0] = pos0[0] + t * (pos1[0] - pos0[0]);
            pt[1] = pos0[1];
            break;
        // Case 1 is the right hand side of the cell (edge 1)
        case 1:
            t     = (isovalue - B) / (D - B);
            pt[0] = pos1[0];
            pt[1] = pos1[1] + t * (pos3[1] - pos1[1]);
            break;
        // Case 2 is the top of the cell (edge 2)
        case 2:
            t     = (isovalue - C) / (D - C);
            pt[0] = pos2[0] + t * (pos3[0] - pos2[0]);
            pt[1] = pos2[1];
            break;
        // Case 4 is the left hand side of the cell (edge 3)
        case 3:
            t     = (isovalue - A) / (C - A);
            pt[0] = pos0[0];
            pt[1] = pos0[1] + t * (pos2[1] - pos0[1]);
            break;
        // Case default is WE MESSED UP CHIEF
        default:
            printf("InterpolateIsoline(%d) messed up!\n", edge);
            break;
    }
}


class SegmentList
{
   public:
                   SegmentList() { maxSegments = 10000; segmentIdx = 0; pts = new float[4*maxSegments]; };
     virtual      ~SegmentList() { delete [] pts; };

     void          AddSegment(float X1, float Y1, float X2, float Y2);
     vtkPolyData  *MakePolyData(void);

   protected:
     float        *pts;
     int           maxSegments;
     int           segmentIdx;
};

void
SegmentList::AddSegment(float X1, float Y1, float X2, float Y2)
{
    pts[4*segmentIdx+0] = X1;
    pts[4*segmentIdx+1] = Y1;
    pts[4*segmentIdx+2] = X2;
    pts[4*segmentIdx+3] = Y2;
    segmentIdx++;
}

vtkPolyData *
SegmentList::MakePolyData(void)
{
    int nsegments = segmentIdx;
    int numPoints = 2*(nsegments);
    vtkPoints *vtk_pts = vtkPoints::New();
    vtk_pts->SetNumberOfPoints(numPoints);
    int ptIdx = 0;
    vtkCellArray *lines = vtkCellArray::New();
    lines->EstimateSize(numPoints,2);
    for (int i = 0 ; i < nsegments ; i++)
    {
        double pt[3];
        pt[0] = pts[4*i];
        pt[1] = pts[4*i+1];
        pt[2] = 0.;
        vtk_pts->SetPoint(ptIdx, pt);
        pt[0] = pts[4*i+2];
        pt[1] = pts[4*i+3];
        pt[2] = 0.;
        vtk_pts->SetPoint(ptIdx+1, pt);
        vtkIdType ids[2] = { ptIdx, ptIdx+1 };
        lines->InsertNextCell(2, ids);
        ptIdx += 2;
    }

    vtkPolyData *pd = vtkPolyData::New();
    pd->SetPoints(vtk_pts);
    pd->SetLines(lines);
    lines->Delete();
    vtk_pts->Delete();

    return pd;
}

int main()
{
    int  i, j, k;

    vtkDataSetReader *rdr = vtkDataSetReader::New();
    rdr->SetFileName("proj5.vtk");
    rdr->Update();

    int dims[3];
    vtkRectilinearGrid *rgrid = (vtkRectilinearGrid *) rdr->GetOutput();
    rgrid->GetDimensions(dims);

    float *X = (float *) rgrid->GetXCoordinates()->GetVoidPointer(0);
    float *Y = (float *) rgrid->GetYCoordinates()->GetVoidPointer(0);
    float *F = (float *) rgrid->GetPointData()->GetScalars()->GetVoidPointer(0);

    // Add 4 segments that put a frame around your isolines.  This also
    // documents how to use "AddSegment".
    SegmentList sl;
    sl.AddSegment(-10, -10, +10, -10); // Add segment (-10,-10) -> (+10, -10)
    sl.AddSegment(-10, +10, +10, +10);
    sl.AddSegment(-10, -10, -10, +10);
    sl.AddSegment(+10, -10, +10, +10);

    // ********************
    // My code for isolines
    // ********************
    int icase; // which case in the global lup table
    int nsegments; // how many segments according to position in lup table
    float A, B, C, D; // the four vertices of the cell
    float pt1[2]; // first point that we will write out with AddSegment
    float pt2[2]; // sceond point that we will write out with AddSegment

    int idx0[3]; int idx1[3]; int idx2[3]; int idx3[3];
    float pos0[2]; float pos1[2]; float pos2[2]; float pos3[2];
    // Explanation of idx0, idx1, idx2, idx 3; pos0, pos1, pos2, pos3:
    //  When looking at a cell, we have four vertices which correspond
    //  to each of these arrays; each of the vertices has both an X and a Y
    //  coordinate.
    //  The idx arrays need to be 3 dimensional because they are used in a call
    //  to GetPointIndex.
    //  The pos ones do not as they are just the "true" X and Y position of the
    //  cell gotten by tossing GetPointIndex calls into the X and Y arrays.
    //  A drawing of a cell and its corresponding variables I have made can be
    //  found in the InterpolateIsoline function.

    for (i=0; i<dims[0]-1; ++i)
    {
        for (j=0; j<dims[1]-1; ++j)
        {
            // Index into the data
            idx0[0] = i;   idx0[1] = j;
            idx1[0] = i+1; idx1[1] = j;
            idx2[0] = i;   idx2[1] = j+1;
            idx3[0] = i+1; idx3[1] = j+1;

            // Positions need to be done after getting the vertex field value
            // because "idx" is modified by the GetPointIndex call
            A = F[GetPointIndex(idx0, dims)];
            pos0[0] = X[idx0[0]];   pos0[1] = Y[idx0[1]];
            B = F[GetPointIndex(idx1, dims)];
            pos1[0] = X[idx1[0]]; pos1[1] = Y[idx1[1]];
            C = F[GetPointIndex(idx2, dims)];
            pos2[0] = X[idx2[0]];   pos2[1] = Y[idx2[1]];
            D = F[GetPointIndex(idx3, dims)];
            pos3[0] = X[idx3[0]]; pos3[1] = Y[idx3[1]];

            // *************************************************************
            // Pseudocode basically ripped from from slide 56 from lecture 7
            // *************************************************************

            // This call is basically what is outlined in the slides; I am just
            // giving it the four vertices (in order) instead of a "cell"
            icase = IdentifyCase(A, B, C, D);
            nsegments = numSegments[icase];
            for (k=0; k<nsegments; ++k)
            {
                int edge1 = lup[icase][2*k];
                InterpolateIsoline(edge1,
                                   A, B, C, D,
                                   pos0, pos1, pos2, pos3,
                                   pt1);
                int edge2 = lup[icase][2*k+1];
                InterpolateIsoline(edge2,
                                   A, B, C, D,
                                   pos0, pos1, pos2, pos3,
                                   pt2);

                // Write the segment
                sl.AddSegment(pt1[0], pt1[1], pt2[0], pt2[1]);
            }
        }
    }

    vtkPolyData *pd = sl.MakePolyData();

    //This can be useful for debugging
/*
    vtkDataSetWriter *writer = vtkDataSetWriter::New();
    writer->SetFileName("paths.vtk");
    writer->SetInputData(pd);
    writer->Write();
 */

    vtkSmartPointer<vtkDataSetMapper> win1Mapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
    win1Mapper->SetInputData(pd);
    win1Mapper->SetScalarRange(0, 0.15);

    vtkSmartPointer<vtkActor> win1Actor =
      vtkSmartPointer<vtkActor>::New();
    win1Actor->SetMapper(win1Mapper);

    vtkSmartPointer<vtkRenderer> ren1 =
      vtkSmartPointer<vtkRenderer>::New();

    vtkSmartPointer<vtkRenderWindow> renWin =
      vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren1);

    vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);
    ren1->AddActor(win1Actor);
    ren1->SetBackground(0.0, 0.0, 0.0);
    renWin->SetSize(800, 800);

    ren1->GetActiveCamera()->SetFocalPoint(0,0,0);
    ren1->GetActiveCamera()->SetPosition(0,0,50);
    ren1->GetActiveCamera()->SetViewUp(0,1,0);
    ren1->GetActiveCamera()->SetClippingRange(20, 120);
    ren1->GetActiveCamera()->SetDistance(30);

    // This starts the event loop and invokes an initial render.
    //
    iren->Initialize();
    iren->Start();

    pd->Delete();
}
