#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDataSetReader.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkLookupTable.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkCamera.h>

// ****************************************************************************
// This does the blue->red interpolation that hank asked for in Proj7D by
// mapping the range 0-255 to the range 0.0-1.0 and setting the lookup table
// values accordingly
// ****************************************************************************
vtkLookupTable * createTable()
{
    vtkLookupTable *lookupTable = vtkLookupTable::New();
    lookupTable->SetNumberOfTableValues(256);

    int i;
    for (i=0; i<255; ++i)
    {
        double slope = 1.0 * (1.0 - 0.0) / (255.0 - 0.0);
        double value = 0.0 + slope * (i - 0.0);
        lookupTable->SetTableValue(i, 1.0-value, 0.0, value);
    }

    return lookupTable;
}

int main(int argc, char *argv[])
{
    // ************************************************************************
    // Hank's setup (reader, data mapper & its actor)
    // ************************************************************************
    vtkDataSetReader *reader = vtkDataSetReader::New();
    reader->SetFileName("noise.vtk");
    reader->Update();

    vtkDataSetMapper *mapper = vtkDataSetMapper::New();
    mapper->SetInputData(reader->GetOutput());

    vtkLookupTable *lut = createTable();
    mapper->SetLookupTable(lut);
    mapper->SetScalarRange(1,6);
    lut->Build();

    vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);

    // ************************************************************************
    // Contour Filter setup
    //     This is Proj7B
    // ************************************************************************
    vtkContourFilter *contour = vtkContourFilter::New();
    contour->SetNumberOfContours(1);
    contour->SetValue(0, 2.4);
    contour->SetValue(1, 4.0);
    contour->SetInputConnection(reader->GetOutputPort());
    contour->Update();

    vtkDataSetMapper *contourMapper = vtkDataSetMapper::New();
    contourMapper->SetInputConnection(contour->GetOutputPort());

    vtkLookupTable *contourLut = createTable();
    contourMapper->ScalarVisibilityOn();
    contourMapper->SetLookupTable(contourLut);
    contourMapper->SetScalarRange(1, 6);
    contourLut->Build();

    vtkActor *contourActor = vtkActor::New();
    contourActor->SetMapper(contourMapper);

    // ************************************************************************
    // Slice setup
    //     This is Proj7C
    // ************************************************************************
    vtkPlane *plane = vtkPlane::New();
    plane->SetNormal(0.0, 0.0, 1.0);

    vtkCutter *cutter = vtkCutter::New();
    cutter->SetCutFunction(plane);
    cutter->SetInputConnection(reader->GetOutputPort());
    cutter->Update();

    vtkLookupTable *cutterLut = createTable();

    vtkDataSetMapper *cutterMapper = vtkDataSetMapper::New();
    cutterMapper->SetInputConnection(cutter->GetOutputPort());
    cutterMapper->SetLookupTable(cutterLut);
    cutterMapper->SetScalarRange(1, 6);
    cutterLut->Build();

    vtkActor *cutterActor = vtkActor::New();
    cutterActor->SetMapper(cutterMapper);

    // ************************************************************************
    // Renderer setup
    // ************************************************************************
    double viewport1[4] = { 0.0, 0.0, 0.5, 1.0 }; // Proj7F
    double viewport2[4] = { 0.5, 0.0, 1.0, 1.0 }; // Proj7F

    vtkRenderer *ren1 = vtkRenderer::New();
    ren1->SetViewport(viewport1); // Proj7F
    ren1->AddActor(cutterActor); // Proj7E

    vtkRenderer *ren2 = vtkRenderer::New();
    ren2->SetViewport(viewport2); // Proj7F
    ren2->AddActor(contourActor); // Proj7E

    vtkRenderWindow *renwin = vtkRenderWindow::New();
    // Proj7A
    renwin->SetSize(768, 768);
    renwin->AddRenderer(ren1);
    renwin->AddRenderer(ren2);

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renwin);

    // Proj7G
    float i;
    for (i=1.00; i<=6.00; i+=0.01)
    {
        // These contours need to be 1 and 2, not 0 and 1... don't know why
        // but when I changed it to that it works
        contour->SetValue(1, i);
        contour->SetValue(2, i);
        contour->Update();
        // The tip to add this code made my cameras not work at all, so I'm
        // going to leave it commented out here. If it makes it work on your
        // machine then uncomment it (I'm running VTK8.1 on Arch Linux x86_64)
        // ren2->GetActiveCamera()->ShallowCopy(ren1->GetActiveCamera());
        renwin->Render();
    }
}

