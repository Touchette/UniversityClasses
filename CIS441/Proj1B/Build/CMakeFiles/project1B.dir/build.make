# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/natalie/Documents/Repos/CIS441/Proj1B/Build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/natalie/Documents/Repos/CIS441/Proj1B/Build

# Include any dependencies generated for this target.
include CMakeFiles/project1B.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project1B.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project1B.dir/flags.make

CMakeFiles/project1B.dir/project1B.cxx.o: CMakeFiles/project1B.dir/flags.make
CMakeFiles/project1B.dir/project1B.cxx.o: project1B.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/natalie/Documents/Repos/CIS441/Proj1B/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project1B.dir/project1B.cxx.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project1B.dir/project1B.cxx.o -c /home/natalie/Documents/Repos/CIS441/Proj1B/Build/project1B.cxx

CMakeFiles/project1B.dir/project1B.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project1B.dir/project1B.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/natalie/Documents/Repos/CIS441/Proj1B/Build/project1B.cxx > CMakeFiles/project1B.dir/project1B.cxx.i

CMakeFiles/project1B.dir/project1B.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project1B.dir/project1B.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/natalie/Documents/Repos/CIS441/Proj1B/Build/project1B.cxx -o CMakeFiles/project1B.dir/project1B.cxx.s

# Object files for target project1B
project1B_OBJECTS = \
"CMakeFiles/project1B.dir/project1B.cxx.o"

# External object files for target project1B
project1B_EXTERNAL_OBJECTS =

project1B: CMakeFiles/project1B.dir/project1B.cxx.o
project1B: CMakeFiles/project1B.dir/build.make
project1B: /usr/bin/vtk/lib/libvtkDomainsChemistryOpenGL2-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersFlowPaths-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersGeneric-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersHyperTree-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersParallelImaging-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersPoints-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersProgrammable-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersSMP-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersSelection-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersTexture-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersTopology-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersVerdict-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkGeovisCore-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOAMR-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOEnSight-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOExodus-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOExportOpenGL2-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOImport-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOInfovis-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOLSDyna-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOMINC-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOMovie-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOPLY-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOParallel-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOParallelXML-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOSQL-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOTecplotTable-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOVideo-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkImagingMorphological-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkImagingStatistics-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkImagingStencil-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkInteractionImage-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkRenderingContextOpenGL2-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkRenderingImage-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkRenderingLOD-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkRenderingVolumeOpenGL2-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkViewsContext2D-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkViewsInfovis-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkDomainsChemistry-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkverdict-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkproj4-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersAMR-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOExport-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkRenderingGL2PSOpenGL2-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkgl2ps-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtklibharu-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtklibxml2-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkoggtheora-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersParallel-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkexoIIc-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOGeometry-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIONetCDF-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtknetcdfcpp-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkNetCDF-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkhdf5_hl-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkhdf5-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkjsoncpp-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkParallelCore-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOLegacy-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtksqlite-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkRenderingOpenGL2-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkglew-8.1.so.1
project1B: /usr/lib/libSM.so
project1B: /usr/lib/libICE.so
project1B: /usr/lib/libX11.so
project1B: /usr/lib/libXext.so
project1B: /usr/lib/libXt.so
project1B: /usr/bin/vtk/lib/libvtkImagingMath-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkChartsCore-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkRenderingContext2D-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersImaging-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkInfovisLayout-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkInfovisCore-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkViewsCore-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkInteractionWidgets-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersHybrid-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkImagingGeneral-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkImagingSources-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersModeling-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkImagingHybrid-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOImage-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkDICOMParser-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkmetaio-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkpng-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtktiff-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkjpeg-8.1.so.1
project1B: /usr/lib/libm.so
project1B: /usr/bin/vtk/lib/libvtkInteractionStyle-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersExtraction-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersStatistics-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkImagingFourier-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkalglib-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkRenderingAnnotation-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkImagingColor-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkRenderingVolume-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkImagingCore-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOXML-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOXMLParser-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkIOCore-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtklz4-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkexpat-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkRenderingLabel-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkRenderingFreeType-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkRenderingCore-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkCommonColor-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersGeometry-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersSources-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersGeneral-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkCommonComputationalGeometry-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkFiltersCore-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkCommonExecutionModel-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkCommonDataModel-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkCommonMisc-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkCommonSystem-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtksys-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkCommonTransforms-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkCommonMath-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkCommonCore-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkfreetype-8.1.so.1
project1B: /usr/bin/vtk/lib/libvtkzlib-8.1.so.1
project1B: CMakeFiles/project1B.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/natalie/Documents/Repos/CIS441/Proj1B/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable project1B"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project1B.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project1B.dir/build: project1B

.PHONY : CMakeFiles/project1B.dir/build

CMakeFiles/project1B.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project1B.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project1B.dir/clean

CMakeFiles/project1B.dir/depend:
	cd /home/natalie/Documents/Repos/CIS441/Proj1B/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/natalie/Documents/Repos/CIS441/Proj1B/Build /home/natalie/Documents/Repos/CIS441/Proj1B/Build /home/natalie/Documents/Repos/CIS441/Proj1B/Build /home/natalie/Documents/Repos/CIS441/Proj1B/Build /home/natalie/Documents/Repos/CIS441/Proj1B/Build/CMakeFiles/project1B.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project1B.dir/depend

