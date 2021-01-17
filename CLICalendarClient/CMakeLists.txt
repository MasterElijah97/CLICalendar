cmake_minimum_required(VERSION 3.16.3)

project(Client VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

find_package(Boost 1.71.0)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
endif()

add_compile_options("-Wall" "-std=c++17")
add_link_options("-pthread" "-lboost_system" "-lboost_thread" "-ldl" "-lsqlite3" "-lncurses")

add_subdirectory(src)
add_subdirectory(include)

add_executable(Client main.cpp)

find_package(SQLite3)
if(SQLite3_FOUND)
	target_include_directories(Client INTERFACE ${SQLite3_INCLUDE_DIRS})
endif()
target_link_libraries(Client PUBLIC 
					ncurses
					${SQLite3_LIBRARIES}
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


