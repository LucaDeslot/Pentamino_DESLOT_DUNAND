# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Pentamino_DESLOT_DUNAND.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Pentamino_DESLOT_DUNAND.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Pentamino_DESLOT_DUNAND.dir/flags.make

CMakeFiles/Pentamino_DESLOT_DUNAND.dir/main.c.o: CMakeFiles/Pentamino_DESLOT_DUNAND.dir/flags.make
CMakeFiles/Pentamino_DESLOT_DUNAND.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Pentamino_DESLOT_DUNAND.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Pentamino_DESLOT_DUNAND.dir/main.c.o   -c /Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND/main.c

CMakeFiles/Pentamino_DESLOT_DUNAND.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Pentamino_DESLOT_DUNAND.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND/main.c > CMakeFiles/Pentamino_DESLOT_DUNAND.dir/main.c.i

CMakeFiles/Pentamino_DESLOT_DUNAND.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Pentamino_DESLOT_DUNAND.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND/main.c -o CMakeFiles/Pentamino_DESLOT_DUNAND.dir/main.c.s

# Object files for target Pentamino_DESLOT_DUNAND
Pentamino_DESLOT_DUNAND_OBJECTS = \
"CMakeFiles/Pentamino_DESLOT_DUNAND.dir/main.c.o"

# External object files for target Pentamino_DESLOT_DUNAND
Pentamino_DESLOT_DUNAND_EXTERNAL_OBJECTS =

Pentamino_DESLOT_DUNAND: CMakeFiles/Pentamino_DESLOT_DUNAND.dir/main.c.o
Pentamino_DESLOT_DUNAND: CMakeFiles/Pentamino_DESLOT_DUNAND.dir/build.make
Pentamino_DESLOT_DUNAND: CMakeFiles/Pentamino_DESLOT_DUNAND.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Pentamino_DESLOT_DUNAND"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Pentamino_DESLOT_DUNAND.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Pentamino_DESLOT_DUNAND.dir/build: Pentamino_DESLOT_DUNAND

.PHONY : CMakeFiles/Pentamino_DESLOT_DUNAND.dir/build

CMakeFiles/Pentamino_DESLOT_DUNAND.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Pentamino_DESLOT_DUNAND.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Pentamino_DESLOT_DUNAND.dir/clean

CMakeFiles/Pentamino_DESLOT_DUNAND.dir/depend:
	cd /Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND /Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND /Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND/cmake-build-debug /Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND/cmake-build-debug /Users/lucadeslot/Documents/Cours/C/Pentamino_DESLOT_DUNAND/cmake-build-debug/CMakeFiles/Pentamino_DESLOT_DUNAND.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Pentamino_DESLOT_DUNAND.dir/depend
