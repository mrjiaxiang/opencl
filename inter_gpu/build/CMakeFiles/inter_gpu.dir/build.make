# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/melody/slam/opencl/inter_gpu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/melody/slam/opencl/inter_gpu/build

# Include any dependencies generated for this target.
include CMakeFiles/inter_gpu.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/inter_gpu.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/inter_gpu.dir/flags.make

CMakeFiles/inter_gpu.dir/main.cpp.o: CMakeFiles/inter_gpu.dir/flags.make
CMakeFiles/inter_gpu.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/melody/slam/opencl/inter_gpu/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/inter_gpu.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/inter_gpu.dir/main.cpp.o -c /home/melody/slam/opencl/inter_gpu/main.cpp

CMakeFiles/inter_gpu.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/inter_gpu.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/melody/slam/opencl/inter_gpu/main.cpp > CMakeFiles/inter_gpu.dir/main.cpp.i

CMakeFiles/inter_gpu.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/inter_gpu.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/melody/slam/opencl/inter_gpu/main.cpp -o CMakeFiles/inter_gpu.dir/main.cpp.s

# Object files for target inter_gpu
inter_gpu_OBJECTS = \
"CMakeFiles/inter_gpu.dir/main.cpp.o"

# External object files for target inter_gpu
inter_gpu_EXTERNAL_OBJECTS =

inter_gpu: CMakeFiles/inter_gpu.dir/main.cpp.o
inter_gpu: CMakeFiles/inter_gpu.dir/build.make
inter_gpu: /usr/lib/x86_64-linux-gnu/libOpenCL.so
inter_gpu: CMakeFiles/inter_gpu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/melody/slam/opencl/inter_gpu/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable inter_gpu"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/inter_gpu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/inter_gpu.dir/build: inter_gpu

.PHONY : CMakeFiles/inter_gpu.dir/build

CMakeFiles/inter_gpu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/inter_gpu.dir/cmake_clean.cmake
.PHONY : CMakeFiles/inter_gpu.dir/clean

CMakeFiles/inter_gpu.dir/depend:
	cd /home/melody/slam/opencl/inter_gpu/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/melody/slam/opencl/inter_gpu /home/melody/slam/opencl/inter_gpu /home/melody/slam/opencl/inter_gpu/build /home/melody/slam/opencl/inter_gpu/build /home/melody/slam/opencl/inter_gpu/build/CMakeFiles/inter_gpu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/inter_gpu.dir/depend
