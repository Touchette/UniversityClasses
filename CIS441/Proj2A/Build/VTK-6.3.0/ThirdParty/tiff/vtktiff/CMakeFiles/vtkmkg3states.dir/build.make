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
include ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/depend.make

# Include the progress variables for this target.
include ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/progress.make

# Include the compile flags for this target's objects.
include ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/flags.make

ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/mkg3states.c.o: ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/flags.make
ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/mkg3states.c.o: ThirdParty/tiff/vtktiff/mkg3states.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/mkg3states.c.o"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/tiff/vtktiff && /usr/bin/gcc-5 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/vtkmkg3states.dir/mkg3states.c.o   -c /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/tiff/vtktiff/mkg3states.c

ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/mkg3states.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/vtkmkg3states.dir/mkg3states.c.i"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/tiff/vtktiff && /usr/bin/gcc-5 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/tiff/vtktiff/mkg3states.c > CMakeFiles/vtkmkg3states.dir/mkg3states.c.i

ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/mkg3states.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/vtkmkg3states.dir/mkg3states.c.s"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/tiff/vtktiff && /usr/bin/gcc-5 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/tiff/vtktiff/mkg3states.c -o CMakeFiles/vtkmkg3states.dir/mkg3states.c.s

# Object files for target vtkmkg3states
vtkmkg3states_OBJECTS = \
"CMakeFiles/vtkmkg3states.dir/mkg3states.c.o"

# External object files for target vtkmkg3states
vtkmkg3states_EXTERNAL_OBJECTS =

bin/vtkmkg3states-6.3: ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/mkg3states.c.o
bin/vtkmkg3states-6.3: ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/build.make
bin/vtkmkg3states-6.3: ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/vtkmkg3states-6.3"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/tiff/vtktiff && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vtkmkg3states.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/build: bin/vtkmkg3states-6.3

.PHONY : ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/build

ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/clean:
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/tiff/vtktiff && $(CMAKE_COMMAND) -P CMakeFiles/vtkmkg3states.dir/cmake_clean.cmake
.PHONY : ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/clean

ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/depend:
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0 /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/tiff/vtktiff /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0 /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/tiff/vtktiff /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ThirdParty/tiff/vtktiff/CMakeFiles/vtkmkg3states.dir/depend

