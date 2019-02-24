# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget vtksys vtkCommonCore vtkCommonMath vtkCommonMisc vtkCommonSystem vtkCommonTransforms vtkCommonDataModel vtkCommonColor vtkCommonExecutionModel vtkFiltersCore vtkCommonComputationalGeometry vtkFiltersGeneral vtkImagingCore vtkImagingFourier vtkalglib vtkFiltersStatistics vtkFiltersExtraction vtkInfovisCore vtkFiltersGeometry vtkFiltersSources vtkRenderingCore vtkzlib vtkfreetype vtkftgl vtkRenderingFreeType vtkRenderingContext2D vtkChartsCore vtkDICOMParser vtkIOCore vtkIOGeometry vtkexpat vtkIOXMLParser vtkIOXML vtkDomainsChemistry vtkIOLegacy vtkHashSource vtkParallelCore vtkFiltersAMR vtkFiltersFlowPaths vtkFiltersGeneric vtkImagingSources vtkFiltersHybrid vtkFiltersHyperTree vtkImagingGeneral vtkFiltersImaging vtkFiltersModeling vtkFiltersParallel vtkFiltersParallelImaging vtkFiltersProgrammable vtkFiltersSMP vtkFiltersSelection vtkFiltersTexture verdict vtkFiltersVerdict vtkmetaio vtkjpeg vtkpng vtkmkg3states vtktiff vtkIOImage vtkImagingHybrid vtkInfovisLayout vtkInteractionStyle vtkImagingColor vtkRenderingAnnotation vtkRenderingVolume vtkInteractionWidgets vtkViewsCore vtkproj4 vtkGeovisCore vtkhdf5 vtkhdf5_hl vtkIOAMR vtkIOEnSight vtkNetCDF vtkNetCDF_cxx vtkexoIIc vtkIOExodus vtkParseOGLExt vtkEncodeString vtkRenderingOpenGL vtkRenderingContextOpenGL vtkgl2ps vtkRenderingGL2PS vtkRenderingLabel vtkIOExport vtkIOImport vtklibxml2 vtkIOInfovis vtkIOLSDyna vtkIOMINC vtkoggtheora vtkIOMovie vtkIONetCDF vtkIOPLY vtkjsoncpp vtkIOParallel vtkIOParallelXML vtksqlite vtkIOSQL vtkIOVideo vtkImagingMath vtkImagingMorphological vtkImagingStatistics vtkImagingStencil vtkInteractionImage vtkRenderingImage vtkRenderingLIC vtkRenderingLOD vtkRenderingVolumeOpenGL vtkViewsContext2D vtkViewsInfovis)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Compute the installation prefix relative to this file.
get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
if(_IMPORT_PREFIX STREQUAL "/")
  set(_IMPORT_PREFIX "")
endif()

# Create imported target vtksys
add_library(vtksys SHARED IMPORTED)

# Create imported target vtkCommonCore
add_library(vtkCommonCore SHARED IMPORTED)

# Create imported target vtkCommonMath
add_library(vtkCommonMath SHARED IMPORTED)

set_target_properties(vtkCommonMath PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonCore"
)

# Create imported target vtkCommonMisc
add_library(vtkCommonMisc SHARED IMPORTED)

set_target_properties(vtkCommonMisc PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonMath"
)

# Create imported target vtkCommonSystem
add_library(vtkCommonSystem SHARED IMPORTED)

set_target_properties(vtkCommonSystem PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonCore"
)

# Create imported target vtkCommonTransforms
add_library(vtkCommonTransforms SHARED IMPORTED)

set_target_properties(vtkCommonTransforms PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkCommonMath"
)

# Create imported target vtkCommonDataModel
add_library(vtkCommonDataModel SHARED IMPORTED)

set_target_properties(vtkCommonDataModel PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonMath;vtkCommonMisc;vtkCommonSystem;vtkCommonTransforms"
)

# Create imported target vtkCommonColor
add_library(vtkCommonColor SHARED IMPORTED)

set_target_properties(vtkCommonColor PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel"
)

# Create imported target vtkCommonExecutionModel
add_library(vtkCommonExecutionModel SHARED IMPORTED)

set_target_properties(vtkCommonExecutionModel PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel"
)

# Create imported target vtkFiltersCore
add_library(vtkFiltersCore SHARED IMPORTED)

set_target_properties(vtkFiltersCore PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkCommonMath;vtkCommonMisc;vtkCommonSystem;vtkCommonTransforms"
)

# Create imported target vtkCommonComputationalGeometry
add_library(vtkCommonComputationalGeometry SHARED IMPORTED)

set_target_properties(vtkCommonComputationalGeometry PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonMath;vtkCommonSystem"
)

# Create imported target vtkFiltersGeneral
add_library(vtkFiltersGeneral SHARED IMPORTED)

set_target_properties(vtkFiltersGeneral PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonComputationalGeometry;vtkFiltersCore"
)

# Create imported target vtkImagingCore
add_library(vtkImagingCore SHARED IMPORTED)

set_target_properties(vtkImagingCore PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonMath;vtkCommonSystem;vtkCommonTransforms"
)

# Create imported target vtkImagingFourier
add_library(vtkImagingFourier SHARED IMPORTED)

set_target_properties(vtkImagingFourier PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkImagingCore"
)

# Create imported target vtkalglib
add_library(vtkalglib SHARED IMPORTED)

# Create imported target vtkFiltersStatistics
add_library(vtkFiltersStatistics SHARED IMPORTED)

set_target_properties(vtkFiltersStatistics PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkCommonMath;vtkCommonMisc;vtkCommonTransforms;vtkImagingFourier;vtkalglib"
)

# Create imported target vtkFiltersExtraction
add_library(vtkFiltersExtraction SHARED IMPORTED)

set_target_properties(vtkFiltersExtraction PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonExecutionModel;vtkFiltersCore;vtkFiltersGeneral;vtkFiltersStatistics"
)

# Create imported target vtkInfovisCore
add_library(vtkInfovisCore SHARED IMPORTED)

set_target_properties(vtkInfovisCore PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonSystem;vtkFiltersExtraction;vtkFiltersGeneral"
)

# Create imported target vtkFiltersGeometry
add_library(vtkFiltersGeometry SHARED IMPORTED)

set_target_properties(vtkFiltersGeometry PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersCore"
)

# Create imported target vtkFiltersSources
add_library(vtkFiltersSources SHARED IMPORTED)

set_target_properties(vtkFiltersSources PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonComputationalGeometry;vtkFiltersGeneral"
)

# Create imported target vtkRenderingCore
add_library(vtkRenderingCore SHARED IMPORTED)

set_target_properties(vtkRenderingCore PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonColor;vtkCommonExecutionModel;vtkCommonTransforms"
)

# Create imported target vtkzlib
add_library(vtkzlib SHARED IMPORTED)

# Create imported target vtkfreetype
add_library(vtkfreetype SHARED IMPORTED)

set_target_properties(vtkfreetype PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkzlib"
)

# Create imported target vtkftgl
add_library(vtkftgl SHARED IMPORTED)

set_target_properties(vtkftgl PROPERTIES
  INTERFACE_LINK_LIBRARIES "/usr/lib/libGL.so;vtkfreetype"
)

# Create imported target vtkRenderingFreeType
add_library(vtkRenderingFreeType SHARED IMPORTED)

set_target_properties(vtkRenderingFreeType PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkRenderingCore;vtkRenderingCore;vtkfreetype;vtkftgl"
)

# Create imported target vtkRenderingContext2D
add_library(vtkRenderingContext2D SHARED IMPORTED)

set_target_properties(vtkRenderingContext2D PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkRenderingCore"
)

# Create imported target vtkChartsCore
add_library(vtkChartsCore SHARED IMPORTED)

set_target_properties(vtkChartsCore PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkRenderingContext2D"
)

# Create imported target vtkDICOMParser
add_library(vtkDICOMParser SHARED IMPORTED)

# Create imported target vtkIOCore
add_library(vtkIOCore SHARED IMPORTED)

set_target_properties(vtkIOCore PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonMisc"
)

# Create imported target vtkIOGeometry
add_library(vtkIOGeometry SHARED IMPORTED)

set_target_properties(vtkIOGeometry PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonMisc;vtkCommonSystem;vtkIOCore"
)

# Create imported target vtkexpat
add_library(vtkexpat SHARED IMPORTED)

# Create imported target vtkIOXMLParser
add_library(vtkIOXMLParser SHARED IMPORTED)

set_target_properties(vtkIOXMLParser PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonMisc;vtkCommonSystem;vtkIOCore"
)

# Create imported target vtkIOXML
add_library(vtkIOXML SHARED IMPORTED)

set_target_properties(vtkIOXML PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkIOGeometry;vtkIOXMLParser"
)

# Create imported target vtkDomainsChemistry
add_library(vtkDomainsChemistry SHARED IMPORTED)

set_target_properties(vtkDomainsChemistry PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkRenderingCore"
)

# Create imported target vtkIOLegacy
add_library(vtkIOLegacy SHARED IMPORTED)

set_target_properties(vtkIOLegacy PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonMisc;vtkCommonSystem;vtkIOCore"
)

# Create imported target vtkHashSource
add_executable(vtkHashSource IMPORTED)

# Create imported target vtkParallelCore
add_library(vtkParallelCore SHARED IMPORTED)

set_target_properties(vtkParallelCore PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkIOLegacy"
)

# Create imported target vtkFiltersAMR
add_library(vtkFiltersAMR SHARED IMPORTED)

set_target_properties(vtkFiltersAMR PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersGeneral;vtkParallelCore"
)

# Create imported target vtkFiltersFlowPaths
add_library(vtkFiltersFlowPaths SHARED IMPORTED)

set_target_properties(vtkFiltersFlowPaths PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkFiltersGeneral;vtkFiltersSources;vtkIOCore"
)

# Create imported target vtkFiltersGeneric
add_library(vtkFiltersGeneric SHARED IMPORTED)

set_target_properties(vtkFiltersGeneric PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersCore;vtkFiltersSources"
)

# Create imported target vtkImagingSources
add_library(vtkImagingSources SHARED IMPORTED)

set_target_properties(vtkImagingSources PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkImagingCore"
)

# Create imported target vtkFiltersHybrid
add_library(vtkFiltersHybrid SHARED IMPORTED)

set_target_properties(vtkFiltersHybrid PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersGeneral;vtkImagingSources;vtkRenderingCore"
)

# Create imported target vtkFiltersHyperTree
add_library(vtkFiltersHyperTree SHARED IMPORTED)

set_target_properties(vtkFiltersHyperTree PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersGeneral"
)

# Create imported target vtkImagingGeneral
add_library(vtkImagingGeneral SHARED IMPORTED)

set_target_properties(vtkImagingGeneral PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkImagingSources"
)

# Create imported target vtkFiltersImaging
add_library(vtkFiltersImaging SHARED IMPORTED)

set_target_properties(vtkFiltersImaging PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersStatistics;vtkImagingGeneral;vtkImagingSources"
)

# Create imported target vtkFiltersModeling
add_library(vtkFiltersModeling SHARED IMPORTED)

set_target_properties(vtkFiltersModeling PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersGeneral;vtkFiltersSources"
)

# Create imported target vtkFiltersParallel
add_library(vtkFiltersParallel SHARED IMPORTED)

set_target_properties(vtkFiltersParallel PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersExtraction;vtkFiltersGeometry;vtkFiltersModeling;vtkParallelCore;vtkRenderingCore"
)

# Create imported target vtkFiltersParallelImaging
add_library(vtkFiltersParallelImaging SHARED IMPORTED)

set_target_properties(vtkFiltersParallelImaging PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersImaging;vtkFiltersParallel;vtkIOLegacy;vtkImagingCore;vtkParallelCore"
)

# Create imported target vtkFiltersProgrammable
add_library(vtkFiltersProgrammable SHARED IMPORTED)

set_target_properties(vtkFiltersProgrammable PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel"
)

# Create imported target vtkFiltersSMP
add_library(vtkFiltersSMP SHARED IMPORTED)

set_target_properties(vtkFiltersSMP PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersCore;vtkFiltersGeneral"
)

# Create imported target vtkFiltersSelection
add_library(vtkFiltersSelection SHARED IMPORTED)

set_target_properties(vtkFiltersSelection PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonComputationalGeometry;vtkFiltersCore"
)

# Create imported target vtkFiltersTexture
add_library(vtkFiltersTexture SHARED IMPORTED)

set_target_properties(vtkFiltersTexture PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersGeneral"
)

# Create imported target verdict
add_library(verdict SHARED IMPORTED)

# Create imported target vtkFiltersVerdict
add_library(vtkFiltersVerdict SHARED IMPORTED)

set_target_properties(vtkFiltersVerdict PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;verdict"
)

# Create imported target vtkmetaio
add_library(vtkmetaio SHARED IMPORTED)

set_target_properties(vtkmetaio PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkzlib"
)

# Create imported target vtkjpeg
add_library(vtkjpeg SHARED IMPORTED)

# Create imported target vtkpng
add_library(vtkpng SHARED IMPORTED)

set_target_properties(vtkpng PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkzlib;-lm"
)

# Create imported target vtkmkg3states
add_executable(vtkmkg3states IMPORTED)

# Create imported target vtktiff
add_library(vtktiff SHARED IMPORTED)

set_target_properties(vtktiff PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkzlib;vtkjpeg;-lm"
)

# Create imported target vtkIOImage
add_library(vtkIOImage SHARED IMPORTED)

set_target_properties(vtkIOImage PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonMath;vtkCommonMisc;vtkCommonSystem;vtkCommonTransforms;vtkIOCore"
)

# Create imported target vtkImagingHybrid
add_library(vtkImagingHybrid SHARED IMPORTED)

set_target_properties(vtkImagingHybrid PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkIOImage;vtkImagingCore"
)

# Create imported target vtkInfovisLayout
add_library(vtkInfovisLayout SHARED IMPORTED)

set_target_properties(vtkInfovisLayout PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkFiltersModeling;vtkImagingHybrid;vtkInfovisCore"
)

# Create imported target vtkInteractionStyle
add_library(vtkInteractionStyle SHARED IMPORTED)

set_target_properties(vtkInteractionStyle PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkRenderingCore"
)

# Create imported target vtkImagingColor
add_library(vtkImagingColor SHARED IMPORTED)

set_target_properties(vtkImagingColor PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkImagingCore"
)

# Create imported target vtkRenderingAnnotation
add_library(vtkRenderingAnnotation SHARED IMPORTED)

set_target_properties(vtkRenderingAnnotation PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkImagingColor;vtkRenderingFreeType"
)

# Create imported target vtkRenderingVolume
add_library(vtkRenderingVolume SHARED IMPORTED)

set_target_properties(vtkRenderingVolume PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkImagingCore;vtkRenderingCore"
)

# Create imported target vtkInteractionWidgets
add_library(vtkInteractionWidgets SHARED IMPORTED)

set_target_properties(vtkInteractionWidgets PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersHybrid;vtkFiltersModeling;vtkImagingGeneral;vtkImagingHybrid;vtkInteractionStyle;vtkRenderingAnnotation;vtkRenderingFreeType;vtkRenderingVolume"
)

# Create imported target vtkViewsCore
add_library(vtkViewsCore SHARED IMPORTED)

set_target_properties(vtkViewsCore PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkInteractionWidgets;vtkRenderingCore"
)

# Create imported target vtkproj4
add_library(vtkproj4 SHARED IMPORTED)

set_target_properties(vtkproj4 PROPERTIES
  INTERFACE_LINK_LIBRARIES "m"
)

# Create imported target vtkGeovisCore
add_library(vtkGeovisCore SHARED IMPORTED)

set_target_properties(vtkGeovisCore PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkIOXML;vtkInfovisLayout;vtkInteractionStyle;vtkInteractionWidgets;vtkRenderingCore;vtkViewsCore;vtkproj4"
)

# Create imported target vtkhdf5
add_library(vtkhdf5 SHARED IMPORTED)

set_target_properties(vtkhdf5 PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "m;dl;vtkzlib"
)

# Create imported target vtkhdf5_hl
add_library(vtkhdf5_hl SHARED IMPORTED)

set_target_properties(vtkhdf5_hl PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "vtkhdf5"
)

# Create imported target vtkIOAMR
add_library(vtkIOAMR SHARED IMPORTED)

set_target_properties(vtkIOAMR PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersAMR;vtkParallelCore"
)

# Create imported target vtkIOEnSight
add_library(vtkIOEnSight SHARED IMPORTED)

set_target_properties(vtkIOEnSight PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel"
)

# Create imported target vtkNetCDF
add_library(vtkNetCDF SHARED IMPORTED)

set_target_properties(vtkNetCDF PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkhdf5_hl;vtkhdf5;m"
)

# Create imported target vtkNetCDF_cxx
add_library(vtkNetCDF_cxx SHARED IMPORTED)

set_target_properties(vtkNetCDF_cxx PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkNetCDF"
)

# Create imported target vtkexoIIc
add_library(vtkexoIIc SHARED IMPORTED)

set_target_properties(vtkexoIIc PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkNetCDF;vtkNetCDF_cxx"
)

# Create imported target vtkIOExodus
add_library(vtkIOExodus SHARED IMPORTED)

set_target_properties(vtkIOExodus PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersGeneral;vtkIOXML"
)

# Create imported target vtkParseOGLExt
add_executable(vtkParseOGLExt IMPORTED)

# Create imported target vtkEncodeString
add_executable(vtkEncodeString IMPORTED)

# Create imported target vtkRenderingOpenGL
add_library(vtkRenderingOpenGL SHARED IMPORTED)

set_target_properties(vtkRenderingOpenGL PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkRenderingCore;/usr/lib/libGL.so;/usr/lib/libGLU.so;/usr/lib/libSM.so;/usr/lib/libICE.so;/usr/lib/libX11.so;/usr/lib/libXext.so;/usr/lib/libXt.so"
)

# Create imported target vtkRenderingContextOpenGL
add_library(vtkRenderingContextOpenGL SHARED IMPORTED)

set_target_properties(vtkRenderingContextOpenGL PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkRenderingContext2D;vtkRenderingOpenGL"
)

# Create imported target vtkgl2ps
add_library(vtkgl2ps SHARED IMPORTED)

set_target_properties(vtkgl2ps PROPERTIES
  INTERFACE_LINK_LIBRARIES "/usr/lib/libGL.so;/usr/lib/libGLU.so;m;vtkzlib;vtkpng;m"
)

# Create imported target vtkRenderingGL2PS
add_library(vtkRenderingGL2PS SHARED IMPORTED)

set_target_properties(vtkRenderingGL2PS PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkRenderingContextOpenGL"
)

# Create imported target vtkRenderingLabel
add_library(vtkRenderingLabel SHARED IMPORTED)

set_target_properties(vtkRenderingLabel PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkRenderingFreeType"
)

# Create imported target vtkIOExport
add_library(vtkIOExport SHARED IMPORTED)

set_target_properties(vtkIOExport PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkImagingCore;vtkRenderingAnnotation;vtkRenderingContext2D;vtkRenderingCore;vtkRenderingFreeType;vtkRenderingGL2PS;vtkRenderingLabel;vtkRenderingOpenGL"
)

# Create imported target vtkIOImport
add_library(vtkIOImport SHARED IMPORTED)

set_target_properties(vtkIOImport PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonCore;vtkRenderingCore;vtksys"
)

# Create imported target vtklibxml2
add_library(vtklibxml2 SHARED IMPORTED)

set_target_properties(vtklibxml2 PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkzlib;dl;-lpthread;dl;m"
)

# Create imported target vtkIOInfovis
add_library(vtkIOInfovis SHARED IMPORTED)

set_target_properties(vtkIOInfovis PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonMisc;vtkCommonSystem;vtkIOCore;vtkIOLegacy;vtkIOXML;vtkInfovisCore"
)

# Create imported target vtkIOLSDyna
add_library(vtkIOLSDyna SHARED IMPORTED)

set_target_properties(vtkIOLSDyna PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkIOXML"
)

# Create imported target vtkIOMINC
add_library(vtkIOMINC SHARED IMPORTED)

set_target_properties(vtkIOMINC PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkFiltersHybrid;vtkIOGeometry;vtkIOImage;vtkRenderingCore"
)

# Create imported target vtkoggtheora
add_library(vtkoggtheora SHARED IMPORTED)

# Create imported target vtkIOMovie
add_library(vtkIOMovie SHARED IMPORTED)

set_target_properties(vtkIOMovie PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonSystem;vtkIOCore;vtkoggtheora"
)

# Create imported target vtkIONetCDF
add_library(vtkIONetCDF SHARED IMPORTED)

set_target_properties(vtkIONetCDF PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonSystem;vtkIOCore"
)

# Create imported target vtkIOPLY
add_library(vtkIOPLY SHARED IMPORTED)

set_target_properties(vtkIOPLY PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel;vtkCommonMisc;vtkIOGeometry"
)

# Create imported target vtkjsoncpp
add_library(vtkjsoncpp SHARED IMPORTED)

# Create imported target vtkIOParallel
add_library(vtkIOParallel SHARED IMPORTED)

set_target_properties(vtkIOParallel PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersParallel;vtkIOImage;vtkIONetCDF;vtkIOXML;vtkParallelCore"
)

# Create imported target vtkIOParallelXML
add_library(vtkIOParallelXML SHARED IMPORTED)

set_target_properties(vtkIOParallelXML PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkIOXML;vtkParallelCore"
)

# Create imported target vtksqlite
add_library(vtksqlite SHARED IMPORTED)

set_target_properties(vtksqlite PROPERTIES
  INTERFACE_LINK_LIBRARIES "-lpthread"
)

# Create imported target vtkIOSQL
add_library(vtkIOSQL SHARED IMPORTED)

set_target_properties(vtkIOSQL PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkIOCore"
)

# Create imported target vtkIOVideo
add_library(vtkIOVideo SHARED IMPORTED)

set_target_properties(vtkIOVideo PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonExecutionModel"
)

# Create imported target vtkImagingMath
add_library(vtkImagingMath SHARED IMPORTED)

set_target_properties(vtkImagingMath PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonDataModel;vtkCommonExecutionModel"
)

# Create imported target vtkImagingMorphological
add_library(vtkImagingMorphological SHARED IMPORTED)

set_target_properties(vtkImagingMorphological PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkImagingCore;vtkImagingGeneral"
)

# Create imported target vtkImagingStatistics
add_library(vtkImagingStatistics SHARED IMPORTED)

set_target_properties(vtkImagingStatistics PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkImagingCore"
)

# Create imported target vtkImagingStencil
add_library(vtkImagingStencil SHARED IMPORTED)

set_target_properties(vtkImagingStencil PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkCommonComputationalGeometry;vtkImagingCore"
)

# Create imported target vtkInteractionImage
add_library(vtkInteractionImage SHARED IMPORTED)

set_target_properties(vtkInteractionImage PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkImagingColor;vtkInteractionStyle;vtkInteractionWidgets;vtkRenderingCore;vtkRenderingFreeType"
)

# Create imported target vtkRenderingImage
add_library(vtkRenderingImage SHARED IMPORTED)

set_target_properties(vtkRenderingImage PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkImagingCore;vtkRenderingCore"
)

# Create imported target vtkRenderingLIC
add_library(vtkRenderingLIC SHARED IMPORTED)

set_target_properties(vtkRenderingLIC PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkIOLegacy;vtkIOXML;vtkImagingSources;vtkRenderingOpenGL"
)

# Create imported target vtkRenderingLOD
add_library(vtkRenderingLOD SHARED IMPORTED)

set_target_properties(vtkRenderingLOD PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkFiltersModeling;vtkRenderingCore"
)

# Create imported target vtkRenderingVolumeOpenGL
add_library(vtkRenderingVolumeOpenGL SHARED IMPORTED)

set_target_properties(vtkRenderingVolumeOpenGL PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkRenderingOpenGL;vtkRenderingVolume"
)

# Create imported target vtkViewsContext2D
add_library(vtkViewsContext2D SHARED IMPORTED)

set_target_properties(vtkViewsContext2D PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkRenderingContext2D;vtkViewsCore"
)

# Create imported target vtkViewsInfovis
add_library(vtkViewsInfovis SHARED IMPORTED)

set_target_properties(vtkViewsInfovis PROPERTIES
  INTERFACE_LINK_LIBRARIES "vtkChartsCore;vtkCommonColor;vtkFiltersImaging;vtkFiltersModeling;vtkInfovisLayout;vtkInteractionStyle;vtkRenderingContext2D;vtkRenderingLabel;vtkViewsCore"
)

if(CMAKE_VERSION VERSION_LESS 2.8.12)
  message(FATAL_ERROR "This file relies on consumers using CMake 2.8.12 or greater.")
endif()

# Load information for each installed configuration.
get_filename_component(_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
file(GLOB CONFIG_FILES "${_DIR}/VTKTargets-*.cmake")
foreach(f ${CONFIG_FILES})
  include(${f})
endforeach()

# Cleanup temporary variables.
set(_IMPORT_PREFIX)

# Loop over all imported files and verify that they actually exist
foreach(target ${_IMPORT_CHECK_TARGETS} )
  foreach(file ${_IMPORT_CHECK_FILES_FOR_${target}} )
    if(NOT EXISTS "${file}" )
      message(FATAL_ERROR "The imported target \"${target}\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    endif()
  endforeach()
  unset(_IMPORT_CHECK_FILES_FOR_${target})
endforeach()
unset(_IMPORT_CHECK_TARGETS)

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
