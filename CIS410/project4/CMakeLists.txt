cmake_minimum_required(VERSION 3.10)

PROJECT(proj4)
SET(VTK_DIR /usr/local/lib/cmake/vtk-8.1)

find_package(VTK REQUIRED)
find_package(Qt5Widgets)
include(${VTK_USE_FILE})

add_executable(proj4 ./proj4.cxx)

SET(CMAKE_CXX_LINK_FLAGS "-OpenGL")
if(VTK_LIBRARIES)
  target_link_libraries(proj4 ${VTK_LIBRARIES})
else()
  target_link_libraries(proj4 vtkHybrid)
endif()


