vtk_module(vtkIOPostgreSQL
  DEPENDS
    vtkCommonDataModel
  PRIVATE_DEPENDS
    vtksys
  IMPLEMENTS
    vtkIOSQL
  TEST_DEPENDS
    vtkTestingIOSQL
    vtkTestingCore
  KIT
    vtkIO
  )
