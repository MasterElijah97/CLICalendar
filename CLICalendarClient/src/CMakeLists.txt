add_library(SEPARATOR
			SEPARATOR.h)
set_target_properties(SEPARATOR PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(SEPARATOR PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(split
			split.h
			split.cpp)

target_include_directories(split PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(spaceFilter
			spaceFilter.h
			spaceFilter.cpp)

target_include_directories(spaceFilter PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(Task
			Task.h
			Task.cpp)

target_include_directories(Task PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(Note
			Note.h
			Note.cpp)

target_include_directories(Note PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(Deal
			Deal.h
			Deal.cpp)

target_include_directories(Deal PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(Important
			Important.h
			Important.cpp)

target_include_directories(Important PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(Day
			Day.h
			Day.cpp)

target_include_directories(Day PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(User
			User.h
			User.cpp)

target_include_directories(User PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(Session
			Session.h
			Session.cpp)

target_include_directories(Session PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(AccountsDbManager
			AccountsDbManager.h
			AccountsDbManager.cpp)

target_include_directories(AccountsDbManager PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(AccessProvider
			AccessProvider.h
			AccessProvider.cpp)

target_include_directories(AccessProvider PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(NetWorker
			NetWorker.h
			NetWorker.cpp)

target_include_directories(NetWorker PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(CommandChecker
			CommandChecker.h
			CommandChecker.cpp)

target_include_directories(CommandChecker PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

