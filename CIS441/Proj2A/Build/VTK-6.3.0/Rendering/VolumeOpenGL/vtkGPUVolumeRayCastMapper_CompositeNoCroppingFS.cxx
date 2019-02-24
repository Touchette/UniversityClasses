/* DO NOT EDIT.
 * Generated by ../../bin/vtkEncodeString-6.3
 * 
 * Define the vtkGPUVolumeRayCastMapper_CompositeNoCroppingFS string.
 *
 * Generated from file: /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/Rendering/VolumeOpenGL/vtkGPUVolumeRayCastMapper_CompositeNoCroppingFS.glsl
 */
#include "vtkGPUVolumeRayCastMapper_CompositeNoCroppingFS.h"
const char *vtkGPUVolumeRayCastMapper_CompositeNoCroppingFS =
"/*=========================================================================\n"
"\n"
"  Program:   Visualization Toolkit\n"
"  Module:    vtkGPUVolumeRayCastMapper_CompositeNoCroppingFS.glsl\n"
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
"// Implementation of some function used by the composite method when cropping\n"
"// is off.\n"
"\n"
"#version 110\n"
"\n"
"// Max intensity is the lowest value.\n"
"vec4 initialColor()\n"
"{\n"
"  return vec4(0.0,0.0,0.0,0.0);\n"
"}\n"
"\n";

