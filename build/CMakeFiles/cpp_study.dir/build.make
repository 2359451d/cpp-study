# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Workspace\cpp_study

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Workspace\cpp_study\build

# Include any dependencies generated for this target.
include CMakeFiles/cpp_study.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cpp_study.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpp_study.dir/flags.make

CMakeFiles/cpp_study.dir/main.cpp.obj: CMakeFiles/cpp_study.dir/flags.make
CMakeFiles/cpp_study.dir/main.cpp.obj: CMakeFiles/cpp_study.dir/includes_CXX.rsp
CMakeFiles/cpp_study.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Workspace\cpp_study\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpp_study.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\cpp_study.dir\main.cpp.obj -c C:\Workspace\cpp_study\main.cpp

CMakeFiles/cpp_study.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpp_study.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Workspace\cpp_study\main.cpp > CMakeFiles\cpp_study.dir\main.cpp.i

CMakeFiles/cpp_study.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpp_study.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Workspace\cpp_study\main.cpp -o CMakeFiles\cpp_study.dir\main.cpp.s

# Object files for target cpp_study
cpp_study_OBJECTS = \
"CMakeFiles/cpp_study.dir/main.cpp.obj"

# External object files for target cpp_study
cpp_study_EXTERNAL_OBJECTS =

cpp_study.exe: CMakeFiles/cpp_study.dir/main.cpp.obj
cpp_study.exe: CMakeFiles/cpp_study.dir/build.make
cpp_study.exe: CMakeFiles/cpp_study.dir/linklibs.rsp
cpp_study.exe: CMakeFiles/cpp_study.dir/objects1.rsp
cpp_study.exe: CMakeFiles/cpp_study.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Workspace\cpp_study\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cpp_study.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cpp_study.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpp_study.dir/build: cpp_study.exe

.PHONY : CMakeFiles/cpp_study.dir/build

CMakeFiles/cpp_study.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cpp_study.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cpp_study.dir/clean

CMakeFiles/cpp_study.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Workspace\cpp_study C:\Workspace\cpp_study C:\Workspace\cpp_study\build C:\Workspace\cpp_study\build C:\Workspace\cpp_study\build\CMakeFiles\cpp_study.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpp_study.dir/depend
