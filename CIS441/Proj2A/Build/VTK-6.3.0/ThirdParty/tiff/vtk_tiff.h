/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtk_tiff.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtk_tiff_h
#define vtk_tiff_h

/* Use the tiff library configured for VTK.  */
/* #undef VTK_USE_SYSTEM_TIFF */
#ifdef VTK_USE_SYSTEM_TIFF
# include <tiffio.h>
#else
# include <vtktiff/tiffio.h>
#endif

#endif
