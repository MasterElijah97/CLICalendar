add_library(SEPARATOR
			SEPARATOR.h)
set_target_properties(SEPARATOR PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(SEPARATOR PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(split
			split.h
			split.cpp)

target_include_directories(split PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(Task
			Task.h
			Task.cpp)

target_include_directories(Task PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(Task PUBLIC split)

add_library(Note
			Note.h
			Note.cpp)

target_include_directories(Note PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(Note PUBLIC split)

add_library(Deal
			Deal.h
			Deal.cpp)

target_include_directories(Deal PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(Deal PUBLIC split)

add_library(Important
			Important.h
			Important.cpp)

target_include_directories(Important PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(Important PUBLIC split)

add_library(Day
			Day.h
			Day.cpp)

target_include_directories(Day PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(Day PUBLIC Deal Important split)

add_library(server
			server.h
			server.cpp)

target_include_directories(server PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(server PUBLIC Task Note Day Deal Important)

add_library(session
			session.h
			session.cpp)

target_include_directories(session PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(session PUBLIC Task Note Day Deal Important)