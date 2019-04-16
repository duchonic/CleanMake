# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.0)
project (cross)

set (CMAKE_CXX_STANDARD 17)

include_directories(
	./
)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (source)
add_subdirectory (customLibs)
add_subdirectory (demo)
add_subdirectory (test)

enable_testing()
add_test(
	TEST1 catch_test
	COMMAND $<TARGET_FILE:cpp_test> --success
)
