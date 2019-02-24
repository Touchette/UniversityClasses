/* DO NOT EDIT.
 * Generated by ../../bin/vtkEncodeString-6.3
 * 
 * Define the vtkLighting_s string.
 *
 * Generated from file: /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/Rendering/OpenGL/vtkLighting_s.glsl
 */
#include "vtkLighting_s.h"
const char *vtkLighting_s =
"// ============================================================================\n"
"//\n"
"//  Program:   Visualization Toolkit\n"
"//  Module:    vtkLighting_s.glsl\n"
"//\n"
"//  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen\n"
"//  All rights reserved.\n"
"//  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.\n"
"//\n"
"//     This software is distributed WITHOUT ANY WARRANTY; without even\n"
"//     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR\n"
"//     PURPOSE.  See the above copyright notice for more information.\n"
"//\n"
"// ============================================================================\n"
"\n"
"// This file defines some lighting functions.\n"
"// They can be used either in a vertex or fragment shader.\n"
"\n"
"#version 110\n"
"\n"
"// Example in vertex shader:\n"
"// Reminder: two-sided/one-sided is controlled by GL_VERTEX_PROGRAM_TWO_SIDE\n"
"//\n"
"// vec4 heyeCoords=gl_ModelViewMatrix*gl_Vertex;\n"
"// vec3 eyeCoords=heyeCoords.xyz/heyeCoords.w;\n"
"// vec3 n=gl_Normalmatrix*gl_Normal;\n"
"// n=normalize(n);\n"
"// separateSpecularColor(gl_FrontMaterial,eyeCoords,n,gl_FrontColor,gl_FrontSecondaryColor);\n"
" // If two-sided.\n"
"// separateSpecularColor(gl_BackMaterial,eyeCoords,n,gl_BackColor,gl_BackSecondaryColor);\n"
"\n"
" // Typical:\n"
"// gl_FrontColor=singleColor(gl_FrontMaterial,eyeCoords,n);\n"
"\n"
"// VTK_LIGHTING_NUMBER_OF_LIGHTS has to be defined (by shader source string\n"
"// concatenation) to be the number of lights on, contiguous from 0 to\n"
"// VTK_LIGHTING_NUMBER_OF_LIGHTS-1\n"
"// it has to be less than gl_MaxLights (typically 8)\n"
"\n"
"// Per light computation\n"
"// (it means the scene ambient term is missing).\n"
"// lightSource is usually as gl_LightSource[i]\n"
"void lightSeparateSpecularColor(gl_LightSourceParameters lightSource,\n"
"                                gl_MaterialParameters m,\n"
"                                vec3 surfacePosEyeCoords,\n"
"                                vec3 n,\n"
"                                bool twoSided,\n"
"                                inout vec4 cpri,\n"
"                                inout vec4 csec)\n"
"{\n"
"  vec3 ldir;\n"
"  vec3 h;\n"
"  float att;\n"
"  float spot;\n"
"  float shininessFactor;\n"
"  vec3 wReverseRayDir=surfacePosEyeCoords;\n"
"\n"
"  if(lightSource.position.w!=0.0)\n"
"    {\n"
"    // ldir=light direction\n"
"    vec3 lightPos=lightSource.position.xyz/lightSource.position.w;\n"
"    ldir=lightPos-surfacePosEyeCoords;\n"
"    float sqrDistance=dot(ldir,ldir);\n"
"    ldir=normalize(ldir);\n"
"    h=normalize(ldir+normalize(wReverseRayDir));\n"
"    att=1.0/(lightSource.constantAttenuation+lightSource.linearAttenuation*sqrt(sqrDistance)+lightSource.quadraticAttenuation*sqrDistance);\n"
"    // USED\n"
"    }\n"
"  else\n"
"    {\n"
"    att=1.0;\n"
"    ldir=lightSource.position.xyz;\n"
"    ldir=normalize(ldir);\n"
"    h=normalize(ldir+wReverseRayDir);\n"
"    }\n"
"\n"
"  if(att>0.0)\n"
"    {\n"
"    // USED\n"
"    if(lightSource.spotCutoff==180.0)\n"
"      {\n"
"      spot=1.0;\n"
"      // NOT USED\n"
"      }\n"
"    else\n"
"      {\n"
"      // USED\n"
"\n"
"      float coef=-dot(ldir,normalize(lightSource.spotDirection));\n"
"      if(coef>=lightSource.spotCosCutoff)\n"
"        {\n"
"        spot=pow(coef,lightSource.spotExponent);\n"
"        // USED\n"
"        }\n"
"      else\n"
"        {\n"
"        spot=0.0;\n"
"        // NOT USED\n"
"        }\n"
"      }\n"
"    if(spot>0.0)\n"
"      {\n"
"      // USED\n"
"\n"
"      // LIT operation...\n"
"      float nDotL=dot(n,ldir);\n"
"      float nDotH=dot(n,h);\n"
"\n"
"      // separate nDotL and nDotH for two-sided shading, otherwise we\n"
"      // get black spots.\n"
"\n"
"      if(nDotL<0.0) // two-sided shading\n"
"        {\n"
"//        nDotL=-nDotL; // mostly NOT USED\n"
"        nDotL=0.0;\n"
"        }\n"
"\n"
"      if(nDotH<0.0) // two-sided shading\n"
"        {\n"
"//        nDotH=-nDotH; // mostly USED, except on the back face of the plane.\n"
"        nDotH=0.0;\n"
"        }\n"
"\n"
"      // ambient term for this light\n"
"      vec4 cpril=m.ambient*lightSource.ambient;// acm*adi\n"
"\n"
"//      cpri=cpril;\n"
"//      return;\n"
"\n"
"      // diffuse term for this light\n"
"      if(nDotL>0.0)\n"
"        {\n"
"        // USED\n"
"        cpril+=m.diffuse*lightSource.diffuse*nDotL; // dcm*dcli\n"
"        }\n"
"\n"
"\n"
"      // specular term for this light\n"
"      shininessFactor=pow(nDotH,m.shininess); // srm\n"
"\n"
"      cpri+=att*spot*cpril;\n"
"\n"
"      // scm*scli\n"
"      csec+=att*spot*\n"
"        m.specular*lightSource.specular*shininessFactor;\n"
"\n"
"      }\n"
"    }\n"
"}\n"
"\n"
"// Ignore Scene ambient. Useful in multipass, if the ambient was already\n"
"// taken into account in a previous pass.\n"
"void initBlackColors(out vec4 cpri,\n"
"                     out vec4 csec)\n"
"{\n"
"  cpri=vec4(0.0,0.0,0.0,1.0);\n"
"  csec=vec4(0.0,0.0,0.0,1.0);\n"
"}\n"
"\n"
"void initColorsWithAmbient(gl_MaterialParameters m,\n"
"                           out vec4 cpri,\n"
"                           out vec4 csec)\n"
"{\n"
"  cpri=m.emission+m.ambient*gl_LightModel.ambient; // ecm+acm*acs\n"
"  csec=vec4(0.0,0.0,0.0,1.0);\n"
"}\n"
"\n"
"#ifdef VTK_LIGHTING_NUMBER_OF_LIGHTS\n"
"\n"
"// This is convenience method to use in shader but you better do\n"
"// this computation on the CPU and send the result as a uniform.\n"
"\n"
"// True if any enabled light is a positional one.\n"
"bool needSurfacePositionInEyeCoordinates()\n"
"{\n"
" int i=0;\n"
" bool result=false;\n"
" while(!result && i<VTK_LIGHTING_NUMBER_OF_LIGHTS)\n"
"  {\n"
"   result=gl_LightSource[i].position.w!=0.0;\n"
"   ++i;\n"
"  }\n"
" return result;\n"
"}\n"
"\n"
"// Lighting computation based on a material m,\n"
"// a position on the surface expressed in eye coordinate (typically a vertex\n"
"//  position in a vertex shader, something interpolated in a fragment shader),\n"
"// a unit normal `n' to the surface in eye coordinates.\n"
"// Most of the components are in cpri (primary color), the specular\n"
"// component is in csec (secondary color).\n"
"// Useful for blending color and textures.\n"
"void separateSpecularColor(gl_MaterialParameters m,\n"
"                           vec3 surfacePosEyeCoords,\n"
"                           vec3 n,\n"
"                           bool twoSided,\n"
"                           out vec4 cpri,\n"
"                           out vec4 csec)\n"
"{\n"
"  initColorsWithAmbient(m,cpri,csec);\n"
"\n"
"  // For each light,\n"
"  int i=0;\n"
"  while(i<VTK_LIGHTING_NUMBER_OF_LIGHTS)\n"
"    {\n"
"    lightSeparateSpecularColor(gl_LightSource[i],m,surfacePosEyeCoords,n,\n"
"                               twoSided,cpri,csec);\n"
"    ++i;\n"
"    }\n"
"}\n"
"\n"
"// Lighting computation based on a material m,\n"
"// a position on the surface expressed in eye coordinate (typically a vertex\n"
"//  position in a vertex shader, something interpolated in a fragment shader),\n"
"// a unit normal to the surface in eye coordinates.\n"
"// The result includes the specular component.\n"
"vec4 singleColor(gl_MaterialParameters m,\n"
"                 vec3 surfacePosEyeCoords,\n"
"                 vec3 n,\n"
"                 bool twoSided)\n"
"{\n"
"  vec4 cpri;\n"
"  vec4 csec;\n"
"  separateSpecularColor(m,surfacePosEyeCoords,n,twoSided,cpri,csec);\n"
"  return cpri+csec;\n"
"}\n"
"\n"
"#endif\n"
"\n";

