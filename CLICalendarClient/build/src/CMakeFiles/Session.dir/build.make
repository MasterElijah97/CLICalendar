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
include src/CMakeFiles/Session.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Session.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Session.dir/flags.make

src/CMakeFiles/Session.dir/Session.cpp.o: src/CMakeFiles/Session.dir/flags.make
src/CMakeFiles/Session.dir/Session.cpp.o: ../src/Session.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/master/CLICalendar/CLICalendarClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/Session.dir/Session.cpp.o"
	cd /home/master/CLICalendar/CLICalendarClient/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Session.dir/Session.cpp.o -c /home/master/CLICalendar/CLICalendarClient/src/Session.cpp

src/CMakeFiles/Session.dir/Session.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Session.dir/Session.cpp.i"
	cd /home/master/CLICalendar/CLICalendarClient/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/master/CLICalendar/CLICalendarClient/src/Session.cpp > CMakeFiles/Session.dir/Session.cpp.i

src/CMakeFiles/Session.dir/Session.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Session.dir/Session.cpp.s"
	cd /home/master/CLICalendar/CLICalendarClient/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/master/CLICalendar/CLICalendarClient/src/Session.cpp -o CMakeFiles/Session.dir/Session.cpp.s

# Object files for target Session
Session_OBJECTS = \
"CMakeFiles/Session.dir/Session.cpp.o"

# External object files for target Session
Session_EXTERNAL_OBJECTS =

src/libSession.a: src/CMakeFiles/Session.dir/Session.cpp.o
src/libSession.a: src/CMakeFiles/Session.dir/build.make
src/libSession.a: src/CMakeFiles/Session.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/master/CLICalendar/CLICalendarClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libSession.a"
	cd /home/master/CLICalendar/CLICalendarClient/build/src && $(CMAKE_COMMAND) -P CMakeFiles/Session.dir/cmake_clean_target.cmake
	cd /home/master/CLICalendar/CLICalendarClient/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Session.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/Session.dir/build: src/libSession.a

.PHONY : src/CMakeFiles/Session.dir/build

src/CMakeFiles/Session.dir/clean:
	cd /home/master/CLICalendar/CLICalendarClient/build/src && $(CMAKE_COMMAND) -P CMakeFiles/Session.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/Session.dir/clean

src/CMakeFiles/Session.dir/depend:
	cd /home/master/CLICalendar/CLICalendarClient/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/master/CLICalendar/CLICalendarClient /home/master/CLICalendar/CLICalendarClient/src /home/master/CLICalendar/CLICalendarClient/build /home/master/CLICalendar/CLICalendarClient/build/src /home/master/CLICalendar/CLICalendarClient/build/src/CMakeFiles/Session.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/Session.dir/depend

