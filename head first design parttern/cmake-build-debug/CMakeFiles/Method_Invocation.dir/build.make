# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/allen/Code_git/Cpp_notes/head first design parttern"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/allen/Code_git/Cpp_notes/head first design parttern/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Method_Invocation.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Method_Invocation.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Method_Invocation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Method_Invocation.dir/flags.make

CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.o: CMakeFiles/Method_Invocation.dir/flags.make
CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.o: ../Method\ Invocation/main\ method\ Invocation.cpp
CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.o: CMakeFiles/Method_Invocation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/allen/Code_git/Cpp_notes/head first design parttern/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.o -MF CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.o.d -o CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.o -c "/Users/allen/Code_git/Cpp_notes/head first design parttern/Method Invocation/main method Invocation.cpp"

CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/allen/Code_git/Cpp_notes/head first design parttern/Method Invocation/main method Invocation.cpp" > CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.i

CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/allen/Code_git/Cpp_notes/head first design parttern/Method Invocation/main method Invocation.cpp" -o CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.s

# Object files for target Method_Invocation
Method_Invocation_OBJECTS = \
"CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.o"

# External object files for target Method_Invocation
Method_Invocation_EXTERNAL_OBJECTS =

Method_Invocation: CMakeFiles/Method_Invocation.dir/Method_Invocation/main_method_Invocation.cpp.o
Method_Invocation: CMakeFiles/Method_Invocation.dir/build.make
Method_Invocation: CMakeFiles/Method_Invocation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/allen/Code_git/Cpp_notes/head first design parttern/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Method_Invocation"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Method_Invocation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Method_Invocation.dir/build: Method_Invocation
.PHONY : CMakeFiles/Method_Invocation.dir/build

CMakeFiles/Method_Invocation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Method_Invocation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Method_Invocation.dir/clean

CMakeFiles/Method_Invocation.dir/depend:
	cd "/Users/allen/Code_git/Cpp_notes/head first design parttern/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/allen/Code_git/Cpp_notes/head first design parttern" "/Users/allen/Code_git/Cpp_notes/head first design parttern" "/Users/allen/Code_git/Cpp_notes/head first design parttern/cmake-build-debug" "/Users/allen/Code_git/Cpp_notes/head first design parttern/cmake-build-debug" "/Users/allen/Code_git/Cpp_notes/head first design parttern/cmake-build-debug/CMakeFiles/Method_Invocation.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Method_Invocation.dir/depend

