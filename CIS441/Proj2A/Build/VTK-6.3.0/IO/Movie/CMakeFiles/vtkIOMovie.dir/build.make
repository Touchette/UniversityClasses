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
CMAKE_SOURCE_DIR = /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0

# Include any dependencies generated for this target.
include IO/Movie/CMakeFiles/vtkIOMovie.dir/depend.make

# Include the progress variables for this target.
include IO/Movie/CMakeFiles/vtkIOMovie.dir/progress.make

# Include the compile flags for this target's objects.
include IO/Movie/CMakeFiles/vtkIOMovie.dir/flags.make

IO/Movie/CMakeFiles/vtkIOMovie.dir/vtkGenericMovieWriter.cxx.o: IO/Movie/CMakeFiles/vtkIOMovie.dir/flags.make
IO/Movie/CMakeFiles/vtkIOMovie.dir/vtkGenericMovieWriter.cxx.o: IO/Movie/vtkGenericMovieWriter.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object IO/Movie/CMakeFiles/vtkIOMovie.dir/vtkGenericMovieWriter.cxx.o"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie && /usr/bin/g++-5  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vtkIOMovie.dir/vtkGenericMovieWriter.cxx.o -c /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie/vtkGenericMovieWriter.cxx

IO/Movie/CMakeFiles/vtkIOMovie.dir/vtkGenericMovieWriter.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vtkIOMovie.dir/vtkGenericMovieWriter.cxx.i"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie && /usr/bin/g++-5 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie/vtkGenericMovieWriter.cxx > CMakeFiles/vtkIOMovie.dir/vtkGenericMovieWriter.cxx.i

IO/Movie/CMakeFiles/vtkIOMovie.dir/vtkGenericMovieWriter.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vtkIOMovie.dir/vtkGenericMovieWriter.cxx.s"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie && /usr/bin/g++-5 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie/vtkGenericMovieWriter.cxx -o CMakeFiles/vtkIOMovie.dir/vtkGenericMovieWriter.cxx.s

IO/Movie/CMakeFiles/vtkIOMovie.dir/vtkOggTheoraWriter.cxx.o: IO/Movie/CMakeFiles/vtkIOMovie.dir/flags.make
IO/Movie/CMakeFiles/vtkIOMovie.dir/vtkOggTheoraWriter.cxx.o: IO/Movie/vtkOggTheoraWriter.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object IO/Movie/CMakeFiles/vtkIOMovie.dir/vtkOggTheoraWriter.cxx.o"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie && /usr/bin/g++-5  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vtkIOMovie.dir/vtkOggTheoraWriter.cxx.o -c /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie/vtkOggTheoraWriter.cxx

IO/Movie/CMakeFiles/vtkIOMovie.dir/vtkOggTheoraWriter.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vtkIOMovie.dir/vtkOggTheoraWriter.cxx.i"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie && /usr/bin/g++-5 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie/vtkOggTheoraWriter.cxx > CMakeFiles/vtkIOMovie.dir/vtkOggTheoraWriter.cxx.i

IO/Movie/CMakeFiles/vtkIOMovie.dir/vtkOggTheoraWriter.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vtkIOMovie.dir/vtkOggTheoraWriter.cxx.s"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie && /usr/bin/g++-5 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie/vtkOggTheoraWriter.cxx -o CMakeFiles/vtkIOMovie.dir/vtkOggTheoraWriter.cxx.s

# Object files for target vtkIOMovie
vtkIOMovie_OBJECTS = \
"CMakeFiles/vtkIOMovie.dir/vtkGenericMovieWriter.cxx.o" \
"CMakeFiles/vtkIOMovie.dir/vtkOggTheoraWriter.cxx.o"

# External object files for target vtkIOMovie
vtkIOMovie_EXTERNAL_OBJECTS =

lib/libvtkIOMovie-6.3.so.1: IO/Movie/CMakeFiles/vtkIOMovie.dir/vtkGenericMovieWriter.cxx.o
lib/libvtkIOMovie-6.3.so.1: IO/Movie/CMakeFiles/vtkIOMovie.dir/vtkOggTheoraWriter.cxx.o
lib/libvtkIOMovie-6.3.so.1: IO/Movie/CMakeFiles/vtkIOMovie.dir/build.make
lib/libvtkIOMovie-6.3.so.1: lib/libvtkIOCore-6.3.so.1
lib/libvtkIOMovie-6.3.so.1: lib/libvtkoggtheora-6.3.so.1
lib/libvtkIOMovie-6.3.so.1: lib/libvtkCommonExecutionModel-6.3.so.1
lib/libvtkIOMovie-6.3.so.1: lib/libvtkCommonDataModel-6.3.so.1
lib/libvtkIOMovie-6.3.so.1: lib/libvtkCommonSystem-6.3.so.1
lib/libvtkIOMovie-6.3.so.1: lib/libvtkCommonTransforms-6.3.so.1
lib/libvtkIOMovie-6.3.so.1: lib/libvtkCommonMisc-6.3.so.1
lib/libvtkIOMovie-6.3.so.1: lib/libvtkCommonMath-6.3.so.1
lib/libvtkIOMovie-6.3.so.1: lib/libvtkCommonCore-6.3.so.1
lib/libvtkIOMovie-6.3.so.1: IO/Movie/CMakeFiles/vtkIOMovie.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library ../../lib/libvtkIOMovie-6.3.so"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vtkIOMovie.dir/link.txt --verbose=$(VERBOSE)
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie && $(CMAKE_COMMAND) -E cmake_symlink_library ../../lib/libvtkIOMovie-6.3.so.1 ../../lib/libvtkIOMovie-6.3.so.1 ../../lib/libvtkIOMovie-6.3.so

lib/libvtkIOMovie-6.3.so: lib/libvtkIOMovie-6.3.so.1
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libvtkIOMovie-6.3.so

# Rule to build all files generated by this target.
IO/Movie/CMakeFiles/vtkIOMovie.dir/build: lib/libvtkIOMovie-6.3.so

.PHONY : IO/Movie/CMakeFiles/vtkIOMovie.dir/build

IO/Movie/CMakeFiles/vtkIOMovie.dir/clean:
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie && $(CMAKE_COMMAND) -P CMakeFiles/vtkIOMovie.dir/cmake_clean.cmake
.PHONY : IO/Movie/CMakeFiles/vtkIOMovie.dir/clean

IO/Movie/CMakeFiles/vtkIOMovie.dir/depend:
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0 /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0 /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/IO/Movie/CMakeFiles/vtkIOMovie.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : IO/Movie/CMakeFiles/vtkIOMovie.dir/depend

