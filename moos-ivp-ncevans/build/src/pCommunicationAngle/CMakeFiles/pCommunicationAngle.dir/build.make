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
include src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/depend.make

# Include the progress variables for this target.
include src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/progress.make

# Include the compile flags for this target's objects.
include src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/flags.make

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/flags.make
src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o: ../src/pCommunicationAngle/CommunicationAngle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kfung/Downloads/C++/moos-ivp-ncevans/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o -c /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle/CommunicationAngle.cpp

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.i"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle/CommunicationAngle.cpp > CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.i

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.s"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle/CommunicationAngle.cpp -o CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.s

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o.requires:

.PHONY : src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o.requires

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o.provides: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o.requires
	$(MAKE) -f src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/build.make src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o.provides.build
.PHONY : src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o.provides

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o.provides.build: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o


src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/flags.make
src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o: ../src/pCommunicationAngle/VehicleComms.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kfung/Downloads/C++/moos-ivp-ncevans/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o -c /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle/VehicleComms.cpp

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.i"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle/VehicleComms.cpp > CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.i

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.s"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle/VehicleComms.cpp -o CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.s

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o.requires:

.PHONY : src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o.requires

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o.provides: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o.requires
	$(MAKE) -f src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/build.make src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o.provides.build
.PHONY : src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o.provides

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o.provides.build: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o


src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/flags.make
src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o: ../src/pCommunicationAngle/CommunicationAngle_Info.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kfung/Downloads/C++/moos-ivp-ncevans/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o -c /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle/CommunicationAngle_Info.cpp

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.i"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle/CommunicationAngle_Info.cpp > CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.i

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.s"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle/CommunicationAngle_Info.cpp -o CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.s

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o.requires:

.PHONY : src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o.requires

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o.provides: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o.requires
	$(MAKE) -f src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/build.make src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o.provides.build
.PHONY : src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o.provides

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o.provides.build: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o


src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/flags.make
src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o: ../src/pCommunicationAngle/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kfung/Downloads/C++/moos-ivp-ncevans/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pCommunicationAngle.dir/main.cpp.o -c /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle/main.cpp

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pCommunicationAngle.dir/main.cpp.i"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle/main.cpp > CMakeFiles/pCommunicationAngle.dir/main.cpp.i

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pCommunicationAngle.dir/main.cpp.s"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle/main.cpp -o CMakeFiles/pCommunicationAngle.dir/main.cpp.s

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o.requires:

.PHONY : src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o.requires

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o.provides: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o.requires
	$(MAKE) -f src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/build.make src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o.provides.build
.PHONY : src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o.provides

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o.provides.build: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o


# Object files for target pCommunicationAngle
pCommunicationAngle_OBJECTS = \
"CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o" \
"CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o" \
"CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o" \
"CMakeFiles/pCommunicationAngle.dir/main.cpp.o"

# External object files for target pCommunicationAngle
pCommunicationAngle_EXTERNAL_OBJECTS =

../bin/pCommunicationAngle: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o
../bin/pCommunicationAngle: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o
../bin/pCommunicationAngle: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o
../bin/pCommunicationAngle: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o
../bin/pCommunicationAngle: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/build.make
../bin/pCommunicationAngle: /home/kfung/Downloads/C++/moos-ivp/build/MOOS/MOOSCore/lib/libMOOS.a
../bin/pCommunicationAngle: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kfung/Downloads/C++/moos-ivp-ncevans/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../../../bin/pCommunicationAngle"
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pCommunicationAngle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/build: ../bin/pCommunicationAngle

.PHONY : src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/build

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/requires: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle.cpp.o.requires
src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/requires: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/VehicleComms.cpp.o.requires
src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/requires: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/CommunicationAngle_Info.cpp.o.requires
src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/requires: src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/main.cpp.o.requires

.PHONY : src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/requires

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/clean:
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle && $(CMAKE_COMMAND) -P CMakeFiles/pCommunicationAngle.dir/cmake_clean.cmake
.PHONY : src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/clean

src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/depend:
	cd /home/kfung/Downloads/C++/moos-ivp-ncevans/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kfung/Downloads/C++/moos-ivp-ncevans /home/kfung/Downloads/C++/moos-ivp-ncevans/src/pCommunicationAngle /home/kfung/Downloads/C++/moos-ivp-ncevans/build /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle /home/kfung/Downloads/C++/moos-ivp-ncevans/build/src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/pCommunicationAngle/CMakeFiles/pCommunicationAngle.dir/depend

