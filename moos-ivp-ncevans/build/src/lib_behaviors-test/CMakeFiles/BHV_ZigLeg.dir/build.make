# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/kfung/Downloads/C++/moos-ivp-ncevans

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kfung/Downloads/C++/moos-ivp-ncevans/build

# Include any dependencies generated for this target.
include src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/depend.make

# Include the progress variables for this target.
include src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/progress.make

# Include the compile flags for this target's objects.
include src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/flags.make

src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o: src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/flags.make
src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o: ../src/lib_behaviors-test/BHV_ZigLeg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kfung/Downloads/C++/moos-ivp-ncevans/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/lib_behaviors-test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o -c /home/kfung/Downloads/C++/moos-ivp-ncevans/src/lib_behaviors-test/BHV_ZigLeg.cpp

src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.i"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/lib_behaviors-test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kfung/Downloads/C++/moos-ivp-ncevans/src/lib_behaviors-test/BHV_ZigLeg.cpp > CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.i

src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.s"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/lib_behaviors-test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kfung/Downloads/C++/moos-ivp-ncevans/src/lib_behaviors-test/BHV_ZigLeg.cpp -o CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.s

src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o.requires:

.PHONY : src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o.requires

src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o.provides: src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o.requires
	$(MAKE) -f src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/build.make src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o.provides.build
.PHONY : src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o.provides

src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o.provides.build: src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o


# Object files for target BHV_ZigLeg
BHV_ZigLeg_OBJECTS = \
"CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o"

# External object files for target BHV_ZigLeg
BHV_ZigLeg_EXTERNAL_OBJECTS =

../lib/libBHV_ZigLeg.so: src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o
../lib/libBHV_ZigLeg.so: src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/build.make
../lib/libBHV_ZigLeg.so: src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kfung/Downloads/C++/moos-ivp-ncevans/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../../../lib/libBHV_ZigLeg.so"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/lib_behaviors-test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BHV_ZigLeg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/build: ../lib/libBHV_ZigLeg.so

.PHONY : src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/build

src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/requires: src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/BHV_ZigLeg.cpp.o.requires

.PHONY : src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/requires

src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/clean:
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/lib_behaviors-test && $(CMAKE_COMMAND) -P CMakeFiles/BHV_ZigLeg.dir/cmake_clean.cmake
.PHONY : src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/clean

src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/depend:
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kfung/Downloads/C++/moos-ivp-ncevans /home/kfung/Downloads/C++/moos-ivp-ncevans/src/lib_behaviors-test /home/kfung/Downloads/C++/moos-ivp-ncevans/build /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/lib_behaviors-test /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/lib_behaviors-test/CMakeFiles/BHV_ZigLeg.dir/depend

