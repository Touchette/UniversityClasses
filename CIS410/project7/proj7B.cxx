#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDataSetReader.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkLookupTable.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataMapper.h>


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

    vtkLookupTable *lut = vtkLookupTable::New();
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

    vtkLookupTable *contourLut = vtkLookupTable::New();
    contourMapper->ScalarVisibilityOn();
    contourMapper->SetLookupTable(contourLut);
    contourMapper->SetScalarRange(1, 6);
    contourLut->Build();

    vtkActor *contourActor = vtkActor::New();
    contourActor->SetMapper(contourMapper);

    // ************************************************************************
    // Renderer setup
    // ************************************************************************
    vtkRenderer *ren = vtkRenderer::New();
    // ren->AddActor(actor);
    ren->AddActor(contourActor);

    vtkRenderWindow *renwin = vtkRenderWindow::New();
    renwin->SetSize(768, 768);
    renwin->AddRenderer(ren);

    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renwin);
    renwin->Render();
    iren->Initialize();
    iren->Start();
}

