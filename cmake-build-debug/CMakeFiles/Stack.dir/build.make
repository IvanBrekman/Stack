# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/ivanbrekman/programms/clion-2021.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/ivanbrekman/programms/clion-2021.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ivanbrekman/CLionProjects/Stack

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivanbrekman/CLionProjects/Stack/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Stack.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Stack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Stack.dir/flags.make

CMakeFiles/Stack.dir/main.cpp.o: CMakeFiles/Stack.dir/flags.make
CMakeFiles/Stack.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivanbrekman/CLionProjects/Stack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Stack.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Stack.dir/main.cpp.o -c /home/ivanbrekman/CLionProjects/Stack/main.cpp

CMakeFiles/Stack.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Stack.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivanbrekman/CLionProjects/Stack/main.cpp > CMakeFiles/Stack.dir/main.cpp.i

CMakeFiles/Stack.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Stack.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivanbrekman/CLionProjects/Stack/main.cpp -o CMakeFiles/Stack.dir/main.cpp.s

CMakeFiles/Stack.dir/stack.cpp.o: CMakeFiles/Stack.dir/flags.make
CMakeFiles/Stack.dir/stack.cpp.o: ../stack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivanbrekman/CLionProjects/Stack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Stack.dir/stack.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Stack.dir/stack.cpp.o -c /home/ivanbrekman/CLionProjects/Stack/stack.cpp

CMakeFiles/Stack.dir/stack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Stack.dir/stack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivanbrekman/CLionProjects/Stack/stack.cpp > CMakeFiles/Stack.dir/stack.cpp.i

CMakeFiles/Stack.dir/stack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Stack.dir/stack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivanbrekman/CLionProjects/Stack/stack.cpp -o CMakeFiles/Stack.dir/stack.cpp.s

CMakeFiles/Stack.dir/errorlib.cpp.o: CMakeFiles/Stack.dir/flags.make
CMakeFiles/Stack.dir/errorlib.cpp.o: ../errorlib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivanbrekman/CLionProjects/Stack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Stack.dir/errorlib.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Stack.dir/errorlib.cpp.o -c /home/ivanbrekman/CLionProjects/Stack/errorlib.cpp

CMakeFiles/Stack.dir/errorlib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Stack.dir/errorlib.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivanbrekman/CLionProjects/Stack/errorlib.cpp > CMakeFiles/Stack.dir/errorlib.cpp.i

CMakeFiles/Stack.dir/errorlib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Stack.dir/errorlib.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivanbrekman/CLionProjects/Stack/errorlib.cpp -o CMakeFiles/Stack.dir/errorlib.cpp.s

CMakeFiles/Stack.dir/tests/test.cpp.o: CMakeFiles/Stack.dir/flags.make
CMakeFiles/Stack.dir/tests/test.cpp.o: ../tests/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivanbrekman/CLionProjects/Stack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Stack.dir/tests/test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Stack.dir/tests/test.cpp.o -c /home/ivanbrekman/CLionProjects/Stack/tests/test.cpp

CMakeFiles/Stack.dir/tests/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Stack.dir/tests/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ivanbrekman/CLionProjects/Stack/tests/test.cpp > CMakeFiles/Stack.dir/tests/test.cpp.i

CMakeFiles/Stack.dir/tests/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Stack.dir/tests/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ivanbrekman/CLionProjects/Stack/tests/test.cpp -o CMakeFiles/Stack.dir/tests/test.cpp.s

# Object files for target Stack
Stack_OBJECTS = \
"CMakeFiles/Stack.dir/main.cpp.o" \
"CMakeFiles/Stack.dir/stack.cpp.o" \
"CMakeFiles/Stack.dir/errorlib.cpp.o" \
"CMakeFiles/Stack.dir/tests/test.cpp.o"

# External object files for target Stack
Stack_EXTERNAL_OBJECTS =

Stack: CMakeFiles/Stack.dir/main.cpp.o
Stack: CMakeFiles/Stack.dir/stack.cpp.o
Stack: CMakeFiles/Stack.dir/errorlib.cpp.o
Stack: CMakeFiles/Stack.dir/tests/test.cpp.o
Stack: CMakeFiles/Stack.dir/build.make
Stack: CMakeFiles/Stack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ivanbrekman/CLionProjects/Stack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Stack"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Stack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Stack.dir/build: Stack
.PHONY : CMakeFiles/Stack.dir/build

CMakeFiles/Stack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Stack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Stack.dir/clean

CMakeFiles/Stack.dir/depend:
	cd /home/ivanbrekman/CLionProjects/Stack/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivanbrekman/CLionProjects/Stack /home/ivanbrekman/CLionProjects/Stack /home/ivanbrekman/CLionProjects/Stack/cmake-build-debug /home/ivanbrekman/CLionProjects/Stack/cmake-build-debug /home/ivanbrekman/CLionProjects/Stack/cmake-build-debug/CMakeFiles/Stack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Stack.dir/depend

