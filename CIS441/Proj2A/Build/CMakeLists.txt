cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(project1F)
SET(VTK_DIR /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(project2A project2A)

if(VTK_LIBRARIES)
		target_link_libraries(project2A ${VTK_LIBRARIES})
else()
		target_link_libraries(project2A vtkHybrid)
endif()

