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
    vtkRenderer *ren = vtkRenderer::New();
    // ren->AddActor(actor);
    ren->AddActor(contourActor);
    ren->AddActor(cutterActor);

    vtkRenderWindow *renwin = vtkRenderWindow::New();
    renwin->SetSize(768, 768);
    renwin->AddRenderer(ren);

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renwin);
    renwin->Render();
    iren->Initialize();
    iren->Start();
}

