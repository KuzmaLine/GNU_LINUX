# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kuzmaline/GNU_LINUX/12_InstallPackaging

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kuzmaline/GNU_LINUX/12_InstallPackaging/build

# Include any dependencies generated for this target.
include CMakeFiles/capacity_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/capacity_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/capacity_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/capacity_test.dir/flags.make

CMakeFiles/capacity_test.dir/tests.c.o: CMakeFiles/capacity_test.dir/flags.make
CMakeFiles/capacity_test.dir/tests.c.o: ../tests.c
CMakeFiles/capacity_test.dir/tests.c.o: CMakeFiles/capacity_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuzmaline/GNU_LINUX/12_InstallPackaging/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/capacity_test.dir/tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/capacity_test.dir/tests.c.o -MF CMakeFiles/capacity_test.dir/tests.c.o.d -o CMakeFiles/capacity_test.dir/tests.c.o -c /home/kuzmaline/GNU_LINUX/12_InstallPackaging/tests.c

CMakeFiles/capacity_test.dir/tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/capacity_test.dir/tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kuzmaline/GNU_LINUX/12_InstallPackaging/tests.c > CMakeFiles/capacity_test.dir/tests.c.i

CMakeFiles/capacity_test.dir/tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/capacity_test.dir/tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kuzmaline/GNU_LINUX/12_InstallPackaging/tests.c -o CMakeFiles/capacity_test.dir/tests.c.s

# Object files for target capacity_test
capacity_test_OBJECTS = \
"CMakeFiles/capacity_test.dir/tests.c.o"

# External object files for target capacity_test
capacity_test_EXTERNAL_OBJECTS =

capacity_test: CMakeFiles/capacity_test.dir/tests.c.o
capacity_test: CMakeFiles/capacity_test.dir/build.make
capacity_test: CMakeFiles/capacity_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kuzmaline/GNU_LINUX/12_InstallPackaging/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable capacity_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/capacity_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/capacity_test.dir/build: capacity_test
.PHONY : CMakeFiles/capacity_test.dir/build

CMakeFiles/capacity_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/capacity_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/capacity_test.dir/clean

CMakeFiles/capacity_test.dir/depend:
	cd /home/kuzmaline/GNU_LINUX/12_InstallPackaging/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kuzmaline/GNU_LINUX/12_InstallPackaging /home/kuzmaline/GNU_LINUX/12_InstallPackaging /home/kuzmaline/GNU_LINUX/12_InstallPackaging/build /home/kuzmaline/GNU_LINUX/12_InstallPackaging/build /home/kuzmaline/GNU_LINUX/12_InstallPackaging/build/CMakeFiles/capacity_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/capacity_test.dir/depend

