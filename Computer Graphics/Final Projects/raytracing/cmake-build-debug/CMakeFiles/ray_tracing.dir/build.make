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
CMAKE_SOURCE_DIR = /Users/sami/Desktop/raytracing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sami/Desktop/raytracing/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ray_tracing.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ray_tracing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ray_tracing.dir/flags.make

CMakeFiles/ray_tracing.dir/src/main.cpp.o: CMakeFiles/ray_tracing.dir/flags.make
CMakeFiles/ray_tracing.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sami/Desktop/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ray_tracing.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ray_tracing.dir/src/main.cpp.o -c /Users/sami/Desktop/raytracing/src/main.cpp

CMakeFiles/ray_tracing.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray_tracing.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sami/Desktop/raytracing/src/main.cpp > CMakeFiles/ray_tracing.dir/src/main.cpp.i

CMakeFiles/ray_tracing.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray_tracing.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sami/Desktop/raytracing/src/main.cpp -o CMakeFiles/ray_tracing.dir/src/main.cpp.s

CMakeFiles/ray_tracing.dir/src/bmp.cpp.o: CMakeFiles/ray_tracing.dir/flags.make
CMakeFiles/ray_tracing.dir/src/bmp.cpp.o: ../src/bmp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sami/Desktop/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ray_tracing.dir/src/bmp.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ray_tracing.dir/src/bmp.cpp.o -c /Users/sami/Desktop/raytracing/src/bmp.cpp

CMakeFiles/ray_tracing.dir/src/bmp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray_tracing.dir/src/bmp.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sami/Desktop/raytracing/src/bmp.cpp > CMakeFiles/ray_tracing.dir/src/bmp.cpp.i

CMakeFiles/ray_tracing.dir/src/bmp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray_tracing.dir/src/bmp.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sami/Desktop/raytracing/src/bmp.cpp -o CMakeFiles/ray_tracing.dir/src/bmp.cpp.s

CMakeFiles/ray_tracing.dir/src/camera.cpp.o: CMakeFiles/ray_tracing.dir/flags.make
CMakeFiles/ray_tracing.dir/src/camera.cpp.o: ../src/camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sami/Desktop/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ray_tracing.dir/src/camera.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ray_tracing.dir/src/camera.cpp.o -c /Users/sami/Desktop/raytracing/src/camera.cpp

CMakeFiles/ray_tracing.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray_tracing.dir/src/camera.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sami/Desktop/raytracing/src/camera.cpp > CMakeFiles/ray_tracing.dir/src/camera.cpp.i

CMakeFiles/ray_tracing.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray_tracing.dir/src/camera.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sami/Desktop/raytracing/src/camera.cpp -o CMakeFiles/ray_tracing.dir/src/camera.cpp.s

CMakeFiles/ray_tracing.dir/src/color.cpp.o: CMakeFiles/ray_tracing.dir/flags.make
CMakeFiles/ray_tracing.dir/src/color.cpp.o: ../src/color.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sami/Desktop/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ray_tracing.dir/src/color.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ray_tracing.dir/src/color.cpp.o -c /Users/sami/Desktop/raytracing/src/color.cpp

CMakeFiles/ray_tracing.dir/src/color.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray_tracing.dir/src/color.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sami/Desktop/raytracing/src/color.cpp > CMakeFiles/ray_tracing.dir/src/color.cpp.i

CMakeFiles/ray_tracing.dir/src/color.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray_tracing.dir/src/color.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sami/Desktop/raytracing/src/color.cpp -o CMakeFiles/ray_tracing.dir/src/color.cpp.s

CMakeFiles/ray_tracing.dir/src/light.cpp.o: CMakeFiles/ray_tracing.dir/flags.make
CMakeFiles/ray_tracing.dir/src/light.cpp.o: ../src/light.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sami/Desktop/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ray_tracing.dir/src/light.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ray_tracing.dir/src/light.cpp.o -c /Users/sami/Desktop/raytracing/src/light.cpp

CMakeFiles/ray_tracing.dir/src/light.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray_tracing.dir/src/light.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sami/Desktop/raytracing/src/light.cpp > CMakeFiles/ray_tracing.dir/src/light.cpp.i

CMakeFiles/ray_tracing.dir/src/light.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray_tracing.dir/src/light.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sami/Desktop/raytracing/src/light.cpp -o CMakeFiles/ray_tracing.dir/src/light.cpp.s

CMakeFiles/ray_tracing.dir/src/primitive.cpp.o: CMakeFiles/ray_tracing.dir/flags.make
CMakeFiles/ray_tracing.dir/src/primitive.cpp.o: ../src/primitive.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sami/Desktop/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ray_tracing.dir/src/primitive.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ray_tracing.dir/src/primitive.cpp.o -c /Users/sami/Desktop/raytracing/src/primitive.cpp

CMakeFiles/ray_tracing.dir/src/primitive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray_tracing.dir/src/primitive.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sami/Desktop/raytracing/src/primitive.cpp > CMakeFiles/ray_tracing.dir/src/primitive.cpp.i

CMakeFiles/ray_tracing.dir/src/primitive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray_tracing.dir/src/primitive.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sami/Desktop/raytracing/src/primitive.cpp -o CMakeFiles/ray_tracing.dir/src/primitive.cpp.s

CMakeFiles/ray_tracing.dir/src/raytracer.cpp.o: CMakeFiles/ray_tracing.dir/flags.make
CMakeFiles/ray_tracing.dir/src/raytracer.cpp.o: ../src/raytracer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sami/Desktop/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ray_tracing.dir/src/raytracer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ray_tracing.dir/src/raytracer.cpp.o -c /Users/sami/Desktop/raytracing/src/raytracer.cpp

CMakeFiles/ray_tracing.dir/src/raytracer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray_tracing.dir/src/raytracer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sami/Desktop/raytracing/src/raytracer.cpp > CMakeFiles/ray_tracing.dir/src/raytracer.cpp.i

CMakeFiles/ray_tracing.dir/src/raytracer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray_tracing.dir/src/raytracer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sami/Desktop/raytracing/src/raytracer.cpp -o CMakeFiles/ray_tracing.dir/src/raytracer.cpp.s

CMakeFiles/ray_tracing.dir/src/scene.cpp.o: CMakeFiles/ray_tracing.dir/flags.make
CMakeFiles/ray_tracing.dir/src/scene.cpp.o: ../src/scene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sami/Desktop/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ray_tracing.dir/src/scene.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ray_tracing.dir/src/scene.cpp.o -c /Users/sami/Desktop/raytracing/src/scene.cpp

CMakeFiles/ray_tracing.dir/src/scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray_tracing.dir/src/scene.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sami/Desktop/raytracing/src/scene.cpp > CMakeFiles/ray_tracing.dir/src/scene.cpp.i

CMakeFiles/ray_tracing.dir/src/scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray_tracing.dir/src/scene.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sami/Desktop/raytracing/src/scene.cpp -o CMakeFiles/ray_tracing.dir/src/scene.cpp.s

CMakeFiles/ray_tracing.dir/src/vector3.cpp.o: CMakeFiles/ray_tracing.dir/flags.make
CMakeFiles/ray_tracing.dir/src/vector3.cpp.o: ../src/vector3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sami/Desktop/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ray_tracing.dir/src/vector3.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ray_tracing.dir/src/vector3.cpp.o -c /Users/sami/Desktop/raytracing/src/vector3.cpp

CMakeFiles/ray_tracing.dir/src/vector3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ray_tracing.dir/src/vector3.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sami/Desktop/raytracing/src/vector3.cpp > CMakeFiles/ray_tracing.dir/src/vector3.cpp.i

CMakeFiles/ray_tracing.dir/src/vector3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ray_tracing.dir/src/vector3.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sami/Desktop/raytracing/src/vector3.cpp -o CMakeFiles/ray_tracing.dir/src/vector3.cpp.s

# Object files for target ray_tracing
ray_tracing_OBJECTS = \
"CMakeFiles/ray_tracing.dir/src/main.cpp.o" \
"CMakeFiles/ray_tracing.dir/src/bmp.cpp.o" \
"CMakeFiles/ray_tracing.dir/src/camera.cpp.o" \
"CMakeFiles/ray_tracing.dir/src/color.cpp.o" \
"CMakeFiles/ray_tracing.dir/src/light.cpp.o" \
"CMakeFiles/ray_tracing.dir/src/primitive.cpp.o" \
"CMakeFiles/ray_tracing.dir/src/raytracer.cpp.o" \
"CMakeFiles/ray_tracing.dir/src/scene.cpp.o" \
"CMakeFiles/ray_tracing.dir/src/vector3.cpp.o"

# External object files for target ray_tracing
ray_tracing_EXTERNAL_OBJECTS =

ray_tracing: CMakeFiles/ray_tracing.dir/src/main.cpp.o
ray_tracing: CMakeFiles/ray_tracing.dir/src/bmp.cpp.o
ray_tracing: CMakeFiles/ray_tracing.dir/src/camera.cpp.o
ray_tracing: CMakeFiles/ray_tracing.dir/src/color.cpp.o
ray_tracing: CMakeFiles/ray_tracing.dir/src/light.cpp.o
ray_tracing: CMakeFiles/ray_tracing.dir/src/primitive.cpp.o
ray_tracing: CMakeFiles/ray_tracing.dir/src/raytracer.cpp.o
ray_tracing: CMakeFiles/ray_tracing.dir/src/scene.cpp.o
ray_tracing: CMakeFiles/ray_tracing.dir/src/vector3.cpp.o
ray_tracing: CMakeFiles/ray_tracing.dir/build.make
ray_tracing: CMakeFiles/ray_tracing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sami/Desktop/raytracing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable ray_tracing"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ray_tracing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ray_tracing.dir/build: ray_tracing

.PHONY : CMakeFiles/ray_tracing.dir/build

CMakeFiles/ray_tracing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ray_tracing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ray_tracing.dir/clean

CMakeFiles/ray_tracing.dir/depend:
	cd /Users/sami/Desktop/raytracing/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sami/Desktop/raytracing /Users/sami/Desktop/raytracing /Users/sami/Desktop/raytracing/cmake-build-debug /Users/sami/Desktop/raytracing/cmake-build-debug /Users/sami/Desktop/raytracing/cmake-build-debug/CMakeFiles/ray_tracing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ray_tracing.dir/depend

