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
include CMakeFiles/size_init.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/size_init.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/size_init.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/size_init.dir/flags.make

CMakeFiles/size_init.dir/tests.c.o: CMakeFiles/size_init.dir/flags.make
CMakeFiles/size_init.dir/tests.c.o: ../tests.c
CMakeFiles/size_init.dir/tests.c.o: CMakeFiles/size_init.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kuzmaline/GNU_LINUX/12_InstallPackaging/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/size_init.dir/tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/size_init.dir/tests.c.o -MF CMakeFiles/size_init.dir/tests.c.o.d -o CMakeFiles/size_init.dir/tests.c.o -c /home/kuzmaline/GNU_LINUX/12_InstallPackaging/tests.c

CMakeFiles/size_init.dir/tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/size_init.dir/tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kuzmaline/GNU_LINUX/12_InstallPackaging/tests.c > CMakeFiles/size_init.dir/tests.c.i

CMakeFiles/size_init.dir/tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/size_init.dir/tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kuzmaline/GNU_LINUX/12_InstallPackaging/tests.c -o CMakeFiles/size_init.dir/tests.c.s

# Object files for target size_init
size_init_OBJECTS = \
"CMakeFiles/size_init.dir/tests.c.o"

# External object files for target size_init
size_init_EXTERNAL_OBJECTS =

size_init: CMakeFiles/size_init.dir/tests.c.o
size_init: CMakeFiles/size_init.dir/build.make
size_init: CMakeFiles/size_init.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kuzmaline/GNU_LINUX/12_InstallPackaging/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable size_init"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/size_init.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/size_init.dir/build: size_init
.PHONY : CMakeFiles/size_init.dir/build

CMakeFiles/size_init.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/size_init.dir/cmake_clean.cmake
.PHONY : CMakeFiles/size_init.dir/clean

CMakeFiles/size_init.dir/depend:
	cd /home/kuzmaline/GNU_LINUX/12_InstallPackaging/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kuzmaline/GNU_LINUX/12_InstallPackaging /home/kuzmaline/GNU_LINUX/12_InstallPackaging /home/kuzmaline/GNU_LINUX/12_InstallPackaging/build /home/kuzmaline/GNU_LINUX/12_InstallPackaging/build /home/kuzmaline/GNU_LINUX/12_InstallPackaging/build/CMakeFiles/size_init.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/size_init.dir/depend

