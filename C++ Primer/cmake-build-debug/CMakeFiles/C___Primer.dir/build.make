# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/allen/Code_git/Cpp_notes/C++ Primer"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/allen/Code_git/Cpp_notes/C++ Primer/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/C___Primer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/C___Primer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/C___Primer.dir/flags.make

CMakeFiles/C___Primer.dir/main.cpp.o: CMakeFiles/C___Primer.dir/flags.make
CMakeFiles/C___Primer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/allen/Code_git/Cpp_notes/C++ Primer/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/C___Primer.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/C___Primer.dir/main.cpp.o -c "/Users/allen/Code_git/Cpp_notes/C++ Primer/main.cpp"

CMakeFiles/C___Primer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/C___Primer.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/allen/Code_git/Cpp_notes/C++ Primer/main.cpp" > CMakeFiles/C___Primer.dir/main.cpp.i

CMakeFiles/C___Primer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/C___Primer.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/allen/Code_git/Cpp_notes/C++ Primer/main.cpp" -o CMakeFiles/C___Primer.dir/main.cpp.s

# Object files for target C___Primer
C___Primer_OBJECTS = \
"CMakeFiles/C___Primer.dir/main.cpp.o"

# External object files for target C___Primer
C___Primer_EXTERNAL_OBJECTS =

C___Primer: CMakeFiles/C___Primer.dir/main.cpp.o
C___Primer: CMakeFiles/C___Primer.dir/build.make
C___Primer: CMakeFiles/C___Primer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/allen/Code_git/Cpp_notes/C++ Primer/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable C___Primer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/C___Primer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/C___Primer.dir/build: C___Primer

.PHONY : CMakeFiles/C___Primer.dir/build

CMakeFiles/C___Primer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/C___Primer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/C___Primer.dir/clean

CMakeFiles/C___Primer.dir/depend:
	cd "/Users/allen/Code_git/Cpp_notes/C++ Primer/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/allen/Code_git/Cpp_notes/C++ Primer" "/Users/allen/Code_git/Cpp_notes/C++ Primer" "/Users/allen/Code_git/Cpp_notes/C++ Primer/cmake-build-debug" "/Users/allen/Code_git/Cpp_notes/C++ Primer/cmake-build-debug" "/Users/allen/Code_git/Cpp_notes/C++ Primer/cmake-build-debug/CMakeFiles/C___Primer.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/C___Primer.dir/depend

