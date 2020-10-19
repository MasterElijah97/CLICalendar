cmake_minimum_required(VERSION 3.16.3)

project(Client VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.71.0)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
endif()

add_subdirectory(src)
add_subdirectory(include)

add_executable(Client main.cpp)

add_compile_options(Client "-Wall" "-fexceptions" "-std=c++17")
add_link_options(Client "-lpthread" "-ldl" "-lncurses")

find_package(Curses REQUIRED)
if(Curses_FOUND) 
	target_include_directories(Client INTERFACE ${Curses_INCLUDE_DIR})
endif()

target_link_libraries(Client PRIVATE ${CURSES_LIBRARIES}
										sqlite3
										sqlite_orm
										MD5

										SEPARATOR
										split
										spaceFilter
										Task
										Note
										Deal
										Important
										Day
										User
										Session
										AccountsDbManager
										AccessProvider
										NetWorker
										CommandChecker)


