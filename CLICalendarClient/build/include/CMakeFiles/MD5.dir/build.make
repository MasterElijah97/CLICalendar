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
CMAKE_SOURCE_DIR = /home/master/CLICalendar/CLICalendarClient

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/master/CLICalendar/CLICalendarClient/build

# Include any dependencies generated for this target.
include include/CMakeFiles/MD5.dir/depend.make

# Include the progress variables for this target.
include include/CMakeFiles/MD5.dir/progress.make

# Include the compile flags for this target's objects.
include include/CMakeFiles/MD5.dir/flags.make

include/CMakeFiles/MD5.dir/MD5.cpp.o: include/CMakeFiles/MD5.dir/flags.make
include/CMakeFiles/MD5.dir/MD5.cpp.o: ../include/MD5.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/master/CLICalendar/CLICalendarClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object include/CMakeFiles/MD5.dir/MD5.cpp.o"
	cd /home/master/CLICalendar/CLICalendarClient/build/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MD5.dir/MD5.cpp.o -c /home/master/CLICalendar/CLICalendarClient/include/MD5.cpp

include/CMakeFiles/MD5.dir/MD5.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MD5.dir/MD5.cpp.i"
	cd /home/master/CLICalendar/CLICalendarClient/build/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/master/CLICalendar/CLICalendarClient/include/MD5.cpp > CMakeFiles/MD5.dir/MD5.cpp.i

include/CMakeFiles/MD5.dir/MD5.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MD5.dir/MD5.cpp.s"
	cd /home/master/CLICalendar/CLICalendarClient/build/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/master/CLICalendar/CLICalendarClient/include/MD5.cpp -o CMakeFiles/MD5.dir/MD5.cpp.s

# Object files for target MD5
MD5_OBJECTS = \
"CMakeFiles/MD5.dir/MD5.cpp.o"

# External object files for target MD5
MD5_EXTERNAL_OBJECTS =

include/libMD5.a: include/CMakeFiles/MD5.dir/MD5.cpp.o
include/libMD5.a: include/CMakeFiles/MD5.dir/build.make
include/libMD5.a: include/CMakeFiles/MD5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/master/CLICalendar/CLICalendarClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libMD5.a"
	cd /home/master/CLICalendar/CLICalendarClient/build/include && $(CMAKE_COMMAND) -P CMakeFiles/MD5.dir/cmake_clean_target.cmake
	cd /home/master/CLICalendar/CLICalendarClient/build/include && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MD5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/CMakeFiles/MD5.dir/build: include/libMD5.a

.PHONY : include/CMakeFiles/MD5.dir/build

include/CMakeFiles/MD5.dir/clean:
	cd /home/master/CLICalendar/CLICalendarClient/build/include && $(CMAKE_COMMAND) -P CMakeFiles/MD5.dir/cmake_clean.cmake
.PHONY : include/CMakeFiles/MD5.dir/clean

include/CMakeFiles/MD5.dir/depend:
	cd /home/master/CLICalendar/CLICalendarClient/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/master/CLICalendar/CLICalendarClient /home/master/CLICalendar/CLICalendarClient/include /home/master/CLICalendar/CLICalendarClient/build /home/master/CLICalendar/CLICalendarClient/build/include /home/master/CLICalendar/CLICalendarClient/build/include/CMakeFiles/MD5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/CMakeFiles/MD5.dir/depend

