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
include ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/depend.make

# Include the progress variables for this target.
include ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/progress.make

# Include the compile flags for this target's objects.
include ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/flags.make

ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/lproj.c.o: ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/flags.make
ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/lproj.c.o: ThirdParty/libproj4/vtklibproj4/lproj.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/lproj.c.o"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/libproj4/vtklibproj4 && /usr/bin/gcc-5 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lproj.dir/lproj.c.o   -c /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/libproj4/vtklibproj4/lproj.c

ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/lproj.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lproj.dir/lproj.c.i"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/libproj4/vtklibproj4 && /usr/bin/gcc-5 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/libproj4/vtklibproj4/lproj.c > CMakeFiles/lproj.dir/lproj.c.i

ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/lproj.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lproj.dir/lproj.c.s"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/libproj4/vtklibproj4 && /usr/bin/gcc-5 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/libproj4/vtklibproj4/lproj.c -o CMakeFiles/lproj.dir/lproj.c.s

# Object files for target lproj
lproj_OBJECTS = \
"CMakeFiles/lproj.dir/lproj.c.o"

# External object files for target lproj
lproj_EXTERNAL_OBJECTS =

bin/lproj: ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/lproj.c.o
bin/lproj: ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/build.make
bin/lproj: lib/libvtkproj4-6.3.so.1
bin/lproj: ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/lproj"
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/libproj4/vtklibproj4 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lproj.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/build: bin/lproj

.PHONY : ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/build

ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/clean:
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/libproj4/vtklibproj4 && $(CMAKE_COMMAND) -P CMakeFiles/lproj.dir/cmake_clean.cmake
.PHONY : ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/clean

ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/depend:
	cd /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0 /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/libproj4/vtklibproj4 /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0 /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/libproj4/vtklibproj4 /home/natalie/Documents/Repos/UniversityClasses/CIS441/Proj2A/Build/VTK-6.3.0/ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ThirdParty/libproj4/vtklibproj4/CMakeFiles/lproj.dir/depend
