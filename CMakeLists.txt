# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.0)
project (cross)

set (CMAKE_CXX_STANDARD 11)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	message(STATUS "Made with Linux")
	add_definitions(-DIS_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	message(STATUS "Made with Windows")
	add_definitions(-DIS_WINDOWS)
else()
	add_definitions(-DIS_MAC)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	message(STATUS "Visual Studio C++")
	add_definitions(-DIS_VISUAL_STUDIO -D_HAS_AUTO_PTR_ETC)
	#debug
	set(CMAKE_CXX_FLAGS "/EHsc /MDd /Zi /Ob0 /Od /RTC1 /Wall")
	#release
	#set(CMAKE_CXX_FLAGS_RELEASE "/MD /O2 /Ob2 /DNDEBUG")
endif()

include_directories( ./ )

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "add windows include folders")
	include_directories(
		"C:/cLibs/xmlwrapp/include"
		"C:/cLibs/libxml2-2.7.8.win32/include"
		"C:/cLibs/iconv-1.9.2.win32/include"
	)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	message(STATUS "add linux include folders")
	include_directories(
		#/opt/gsm1101/host/usr/i586-buildroot-linux-uclibc/sysroot/usr/include
	)

endif()

add_subdirectory (source)
add_subdirectory (customLibs)
add_subdirectory (demo)
add_subdirectory (test)

enable_testing()
add_test(
	TEST1 catch_test
	COMMAND $<TARGET_FILE:testing> --success
)
