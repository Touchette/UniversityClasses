#!/usr/bin/env python

# This example demonstrates the use and manipulation of lookup tables.

import vtk
from vtk.util.colors import *
from vtk.util.misc import vtkGetDataRoot
VTK_DATA_ROOT = vtkGetDataRoot()

# First create pipeline a simple pipeline that reads a structure grid
# and then extracts a plane from the grid. The plane will be colored
# differently by using different lookup tables.
#
# Note: the Update method is manually invoked because it causes the
# reader to read; later on we use the output of the reader to set
# a range for the scalar values.
pl3d = vtk.vtkMultiBlockPLOT3DReader()
pl3d.SetXYZFileName(VTK_DATA_ROOT + "/Data/combxyz.bin")
pl3d.SetQFileName(VTK_DATA_ROOT + "/Data/combq.bin")
pl3d.SetScalarFunctionNumber(100)
pl3d.SetVectorFunctionNumber(202)
pl3d.Update()
pl3d_output = pl3d.GetOutput().GetBlock(0)

plane = vtk.vtkStructuredGridGeometryFilter()
plane.SetInputData(pl3d_output)
plane.SetExtent(1, 100, 1, 100, 7, 7)
lut = vtk.vtkLookupTable()
planeMapper = vtk.vtkPolyDataMapper()
planeMapper.SetLookupTable(lut)
planeMapper.SetInputConnection(plane.GetOutputPort())
planeMapper.SetScalarRange(pl3d_output.GetScalarRange())
planeActor = vtk.vtkActor()
planeActor.SetMapper(planeMapper)

# This creates an outline around the data.
outline = vtk.vtkStructuredGridOutlineFilter()
outline.SetInputData(pl3d_output)
outlineMapper = vtk.vtkPolyDataMapper()
outlineMapper.SetInputConnection(outline.GetOutputPort())
outlineActor = vtk.vtkActor()
outlineActor.SetMapper(outlineMapper)

# Much of the following is commented out. To try different lookup tables,
# uncommented the appropriate portions.

# This creates a black to white lut.
##lut.SetHueRange(0, 0)
##lut.SetSaturationRange(0, 0)
##lut.SetValueRange(0.2, 1.0)

# This creates a red to blue lut.
##lut.SetHueRange(0.0, 0.667)

# This creates a blue to red lut.
##lut.SetHueRange(0.667, 0.0)

# This creates a wierd effect. The Build() method causes the lookup
# table to allocate memory and create a table based on the currect
# hue, saturation, value, and alpha (transparency) range. Here we then
# manually overwrite the values generated by the Build() method.
lut.SetNumberOfColors(256)
lut.Build()
for i in range(0, 16):
    lut.SetTableValue(i*16, red[0], red[1], red[2], 1)
    lut.SetTableValue(i*16+1, green[0], green[1], green[2], 1)
    lut.SetTableValue(i*16+2, blue[0], blue[1], blue[2], 1)
    lut.SetTableValue(i*16+3, black[0], black[1], black[2], 1)


# Create the RenderWindow, Renderer and both Actors
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

# Add the actors to the renderer, set the background and size
ren.AddActor(outlineActor)
ren.AddActor(planeActor)

ren.SetBackground(0.1, 0.2, 0.4)
ren.TwoSidedLightingOff()

renWin.SetSize(250, 250)

cam1 = ren.GetActiveCamera()
cam1.SetClippingRange(3.95297, 50)
cam1.SetFocalPoint(8.88908, 0.595038, 29.3342)
cam1.SetPosition(-12.3332, 31.7479, 41.2387)
cam1.SetViewUp(0.060772, -0.319905, 0.945498)

iren.Initialize()
renWin.Render()
iren.Start()
