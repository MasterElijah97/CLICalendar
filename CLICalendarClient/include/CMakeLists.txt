add_library(MD5
			MD5.h
			MD5.cpp)

target_include_directories(MD5 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(sqlite_orm
			sqlite_orm.h)
set_target_properties(sqlite_orm PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(sqlite_orm PUBLIC sqlite3)
target_include_directories(sqlite_orm PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
