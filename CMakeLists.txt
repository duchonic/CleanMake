# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.0)
project (cross)

set (CMAKE_CXX_STANDARD 17)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	message(STATUS "Made with Linux")
	add_definitions(-DIS_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	message(STATUS "Made with Windows")
	add_definitions(-DIS_WINDOWS)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	message(STATUS "Visual Studio C++")
	add_definitions(-DIS_VISUAL_STUDIO)
endif()

include_directories(
	./
)

add_subdirectory (source)
add_subdirectory (customLibs)
add_subdirectory (demo)
add_subdirectory (test)

enable_testing()
add_test(
	TEST1 catch_test
	COMMAND $<TARGET_FILE:cpp_test> --success
)
