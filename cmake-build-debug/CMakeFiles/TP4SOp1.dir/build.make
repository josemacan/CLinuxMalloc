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
CMAKE_COMMAND = /snap/clion/114/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/114/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/admint/CLionProjects/TP4SOp1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/admint/CLionProjects/TP4SOp1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TP4SOp1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TP4SOp1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TP4SOp1.dir/flags.make

CMakeFiles/TP4SOp1.dir/main.c.o: CMakeFiles/TP4SOp1.dir/flags.make
CMakeFiles/TP4SOp1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/admint/CLionProjects/TP4SOp1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TP4SOp1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TP4SOp1.dir/main.c.o   -c /home/admint/CLionProjects/TP4SOp1/main.c

CMakeFiles/TP4SOp1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TP4SOp1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/admint/CLionProjects/TP4SOp1/main.c > CMakeFiles/TP4SOp1.dir/main.c.i

CMakeFiles/TP4SOp1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TP4SOp1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/admint/CLionProjects/TP4SOp1/main.c -o CMakeFiles/TP4SOp1.dir/main.c.s

# Object files for target TP4SOp1
TP4SOp1_OBJECTS = \
"CMakeFiles/TP4SOp1.dir/main.c.o"

# External object files for target TP4SOp1
TP4SOp1_EXTERNAL_OBJECTS =

TP4SOp1: CMakeFiles/TP4SOp1.dir/main.c.o
TP4SOp1: CMakeFiles/TP4SOp1.dir/build.make
TP4SOp1: CMakeFiles/TP4SOp1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/admint/CLionProjects/TP4SOp1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable TP4SOp1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP4SOp1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TP4SOp1.dir/build: TP4SOp1

.PHONY : CMakeFiles/TP4SOp1.dir/build

CMakeFiles/TP4SOp1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TP4SOp1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TP4SOp1.dir/clean

CMakeFiles/TP4SOp1.dir/depend:
	cd /home/admint/CLionProjects/TP4SOp1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/admint/CLionProjects/TP4SOp1 /home/admint/CLionProjects/TP4SOp1 /home/admint/CLionProjects/TP4SOp1/cmake-build-debug /home/admint/CLionProjects/TP4SOp1/cmake-build-debug /home/admint/CLionProjects/TP4SOp1/cmake-build-debug/CMakeFiles/TP4SOp1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TP4SOp1.dir/depend

