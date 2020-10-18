cmake_minimum_required(VERSION 3.16.3)
project(CLICalendarClient VERSION 1.0.0 LANGUAGES C CXX)

SET(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.71.0)
if(Boost_FOUND)
	message(STATUS "BOOST FOUND !")
	include_directories(${Boost_INCLUDE_DIRS})
	include_directories(${CURSES_INCLUDE_DIR})
	include_directories("src/")
	include_directories("include/")
	add_executable(CLICalendarClient main.cpp)
	#target_link_directories(CLICalendarClient ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/include)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 
										-Wall 
										-Wpedantic")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread -ldl -lncurses")

	#target_link_libraries(CLICalendarClient ${CURSES_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
ELSE()
	message(STATUS  "BOOST NOT FOUND !")
endif()