/* DO NOT EDIT.
 * Generated by ../../bin/vtkEncodeString-6.3
 * 
 * Define the vtkGPUVolumeRayCastMapper_ParallelProjectionFS string.
 *
 * Generated from file: /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/Rendering/VolumeOpenGL/vtkGPUVolumeRayCastMapper_ParallelProjectionFS.glsl
 */
#include "vtkGPUVolumeRayCastMapper_ParallelProjectionFS.h"
const char *vtkGPUVolumeRayCastMapper_ParallelProjectionFS =
"/*=========================================================================\n"
"\n"
"  Program:   Visualization Toolkit\n"
"  Module:    vtkGPUVolumeRayCastMapper_ParallelProjectionFS.glsl\n"
"\n"
"  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen\n"
"  All rights reserved.\n"
"  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.\n"
"\n"
"     This software is distributed WITHOUT ANY WARRANTY; without even\n"
"     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR\n"
"     PURPOSE.  See the above copyright notice for more information.\n"
"\n"
"=========================================================================*/\n"
"\n"
"// Parallel projection.\n"
"\n"
"#version 110\n"
"\n"
"uniform vec3 parallelRayDirection;\n"
"\n"
"// Incremental vector in texture space (global scope)\n"
"vec3 rayDir;\n"
"\n"
"// Defined in the right projection method.\n"
"void incrementalRayDirection()\n"
"{\n"
"  rayDir=parallelRayDirection;\n"
"}\n"
"\n";

