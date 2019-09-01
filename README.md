# CMakeLists.txt

## set project
```
cmake_minimum_required (VERSION 3.0)
project (cross)
```

## set standard
```
set (CMAKE_CXX_STANDARD 17)
```
## ask for system
```
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	add_definitions(-DIS_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_definitions(-DIS_WINDOWS)
else()
	add_definitions(-DIS_MAC)
endif()
```
## add subdirectories
```
add_subdirectory(source)
```
## add library
```
add_library(
	Communication
	SocketConnection.cpp
	serial.cpp
)
```
## add executable
```
add_executable(demo demo.cpp)
```
## build type
```
if(${BUILD_TYPE} STREQUAL "Debug")
```
## link libraries
```
target_link_libraries (
    demo
    LINK_PUBLIC
    Source
    Factory
    CustomLib
    Communication
    Collector
    wsock32
    ws2_32
    "${PROJECT_SOURCE_DIR}/winLibs/debug/ftdi1.lib"
    "${PROJECT_SOURCE_DIR}/winLibs/debug/libiconvStaticD.lib"
    "${PROJECT_SOURCE_DIR}/winLibs/debug/libusb-1.0.lib"
    "${PROJECT_SOURCE_DIR}/winLibs/debug/libxml2-static.lib"
)
```
## add cpack
```
SET(CPACK_GENERATOR "ZIP")
SET(CPACK_PACKAGE_NAME "demopack")
include(CPACK)
```
## add tests
```
enable_testing()
add_test(
	TEST1 catch_test
	COMMAND $<TARGET_FILE:testing> --success
)
```

# running cmake
## setup
```
> git clone https://github.com/duchonic/CleanMake.git
> mkdir build
> cd build
```
## run

### linux
```
> cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=/usr/share/buildroot/toolchainfile.cmake -DBUILD_TYPE=Release -DCMAKE_ECLIPSE_VERSION=4.9 ~/CleanMake/
```
### windows
```
> cmake -G "Visual Studio 16 2019" -A Win32 -DCMAKE_BUILD_TYPE=Debug ../CleanMake
```
### mac
```
> cmake ../CleanMake
```
## create a package
```
> cpack
```