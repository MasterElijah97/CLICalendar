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
include include/CMakeFiles/sqlite_orm.dir/depend.make

# Include the progress variables for this target.
include include/CMakeFiles/sqlite_orm.dir/progress.make

# Include the compile flags for this target's objects.
include include/CMakeFiles/sqlite_orm.dir/flags.make

# Object files for target sqlite_orm
sqlite_orm_OBJECTS =

# External object files for target sqlite_orm
sqlite_orm_EXTERNAL_OBJECTS =

include/libsqlite_orm.a: include/CMakeFiles/sqlite_orm.dir/build.make
include/libsqlite_orm.a: include/CMakeFiles/sqlite_orm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/master/CLICalendar/CLICalendarClient/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX static library libsqlite_orm.a"
	cd /home/master/CLICalendar/CLICalendarClient/build/include && $(CMAKE_COMMAND) -P CMakeFiles/sqlite_orm.dir/cmake_clean_target.cmake
	cd /home/master/CLICalendar/CLICalendarClient/build/include && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sqlite_orm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/CMakeFiles/sqlite_orm.dir/build: include/libsqlite_orm.a

.PHONY : include/CMakeFiles/sqlite_orm.dir/build

include/CMakeFiles/sqlite_orm.dir/clean:
	cd /home/master/CLICalendar/CLICalendarClient/build/include && $(CMAKE_COMMAND) -P CMakeFiles/sqlite_orm.dir/cmake_clean.cmake
.PHONY : include/CMakeFiles/sqlite_orm.dir/clean

include/CMakeFiles/sqlite_orm.dir/depend:
	cd /home/master/CLICalendar/CLICalendarClient/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/master/CLICalendar/CLICalendarClient /home/master/CLICalendar/CLICalendarClient/include /home/master/CLICalendar/CLICalendarClient/build /home/master/CLICalendar/CLICalendarClient/build/include /home/master/CLICalendar/CLICalendarClient/build/include/CMakeFiles/sqlite_orm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/CMakeFiles/sqlite_orm.dir/depend

