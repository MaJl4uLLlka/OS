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
CMAKE_COMMAND = /snap/clion/164/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/164/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/greenboy/Labs/Lab2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/greenboy/Labs/Lab2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Labs.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Labs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Labs.dir/flags.make

CMakeFiles/Labs.dir/main.c.o: CMakeFiles/Labs.dir/flags.make
CMakeFiles/Labs.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/greenboy/Labs/Lab2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Labs.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Labs.dir/main.c.o -c /home/greenboy/Labs/Lab2/main.c

CMakeFiles/Labs.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Labs.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/greenboy/Labs/Lab2/main.c > CMakeFiles/Labs.dir/main.c.i

CMakeFiles/Labs.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Labs.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/greenboy/Labs/Lab2/main.c -o CMakeFiles/Labs.dir/main.c.s

# Object files for target Labs
Labs_OBJECTS = \
"CMakeFiles/Labs.dir/main.c.o"

# External object files for target Labs
Labs_EXTERNAL_OBJECTS =

Labs: CMakeFiles/Labs.dir/main.c.o
Labs: CMakeFiles/Labs.dir/build.make
Labs: CMakeFiles/Labs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/greenboy/Labs/Lab2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Labs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Labs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Labs.dir/build: Labs
.PHONY : CMakeFiles/Labs.dir/build

CMakeFiles/Labs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Labs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Labs.dir/clean

CMakeFiles/Labs.dir/depend:
	cd /home/greenboy/Labs/Lab2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/greenboy/Labs/Lab2 /home/greenboy/Labs/Lab2 /home/greenboy/Labs/Lab2/cmake-build-debug /home/greenboy/Labs/Lab2/cmake-build-debug /home/greenboy/Labs/Lab2/cmake-build-debug/CMakeFiles/Labs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Labs.dir/depend
