# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo/build

# Include any dependencies generated for this target.
include CMakeFiles/modelerVrai.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/modelerVrai.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/modelerVrai.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/modelerVrai.dir/flags.make

CMakeFiles/modelerVrai.dir/modeler.cpp.o: CMakeFiles/modelerVrai.dir/flags.make
CMakeFiles/modelerVrai.dir/modeler.cpp.o: /Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo/modeler.cpp
CMakeFiles/modelerVrai.dir/modeler.cpp.o: CMakeFiles/modelerVrai.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/modelerVrai.dir/modeler.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/modelerVrai.dir/modeler.cpp.o -MF CMakeFiles/modelerVrai.dir/modeler.cpp.o.d -o CMakeFiles/modelerVrai.dir/modeler.cpp.o -c /Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo/modeler.cpp

CMakeFiles/modelerVrai.dir/modeler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/modelerVrai.dir/modeler.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo/modeler.cpp > CMakeFiles/modelerVrai.dir/modeler.cpp.i

CMakeFiles/modelerVrai.dir/modeler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/modelerVrai.dir/modeler.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo/modeler.cpp -o CMakeFiles/modelerVrai.dir/modeler.cpp.s

# Object files for target modelerVrai
modelerVrai_OBJECTS = \
"CMakeFiles/modelerVrai.dir/modeler.cpp.o"

# External object files for target modelerVrai
modelerVrai_EXTERNAL_OBJECTS =

modelerVrai.cpython-311-darwin.so: CMakeFiles/modelerVrai.dir/modeler.cpp.o
modelerVrai.cpython-311-darwin.so: CMakeFiles/modelerVrai.dir/build.make
modelerVrai.cpython-311-darwin.so: libnanobind-static.a
modelerVrai.cpython-311-darwin.so: CMakeFiles/modelerVrai.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module modelerVrai.cpython-311-darwin.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/modelerVrai.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/modelerVrai.dir/build: modelerVrai.cpython-311-darwin.so
.PHONY : CMakeFiles/modelerVrai.dir/build

CMakeFiles/modelerVrai.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/modelerVrai.dir/cmake_clean.cmake
.PHONY : CMakeFiles/modelerVrai.dir/clean

CMakeFiles/modelerVrai.dir/depend:
	cd /Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo /Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo /Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo/build /Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo/build /Users/lise/Desktop/MINES/dep_info/projet_dep/Projet_DepInfo/build/CMakeFiles/modelerVrai.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/modelerVrai.dir/depend

