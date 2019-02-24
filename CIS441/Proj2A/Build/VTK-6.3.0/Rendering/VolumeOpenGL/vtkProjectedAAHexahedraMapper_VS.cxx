/* DO NOT EDIT.
 * Generated by ../../bin/vtkEncodeString-6.3
 * 
 * Define the vtkProjectedAAHexahedraMapper_VS string.
 *
 * Generated from file: /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/Rendering/VolumeOpenGL/vtkProjectedAAHexahedraMapper_VS.glsl
 */
#include "vtkProjectedAAHexahedraMapper_VS.h"
const char *vtkProjectedAAHexahedraMapper_VS =
"/*=========================================================================\n"
"\n"
"  Program:   Visualization Toolkit\n"
"  Module:    vtkGPUVolumeRayCastMapper_HeaderFS.glsl\n"
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
"// High quality volume renderer for axis-aligned hexahedra\n"
"// Implementation by Stephane Marchesin (stephane.marchesin@gmail.com)\n"
"// CEA/DIF - Commissariat a l'Energie Atomique, Centre DAM Ile-De-France\n"
"// BP12, F-91297 Arpajon, France.\n"
"//\n"
"// This file implements the paper\n"
"// \"High-Quality, Semi-Analytical Volume Rendering for AMR Data\",\n"
"// Stephane Marchesin and Guillaume Colin de Verdiere, IEEE Vis 2009.\n"
"\n"
"// inputs of VS\n"
"// vertexpos.xyz : cell position (xmin,ymin,zmin)\n"
"// texcoord0.xyz : cell position (xmax,ymax,zmax)\n"
"// texcoord1.xyzw: node data 0,1,2,3\n"
"// texcoord2.xyzw: node data 4,5,6,7\n"
"\n"
"#version 110\n"
"\n"
"void main()\n"
"{\n"
"  gl_TexCoord[0] = gl_MultiTexCoord0;\n"
"  gl_TexCoord[1] = gl_MultiTexCoord1;\n"
"  gl_TexCoord[2] = gl_MultiTexCoord2;\n"
"  gl_Position = gl_Vertex;\n"
"}\n"
"\n";

