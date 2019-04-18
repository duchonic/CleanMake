# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.


add_library(
	Factory
	OperationFactory.cpp
	ConnectionFactory.cpp
)

add_library(
	Communication
	SocketConnection.cpp
	serial.cpp
)

add_library(
	Collector
	SingletonCollector.cpp
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	add_library (
		Source
		SysOperation.cpp
		#XMLMessage.cpp
		#xmlEventParser.cpp

	)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_library (
		Source
		SysOperation.cpp
		XMLMessage.cpp
		xmlEventParser.cpp
	)
else()
	add_library (
		Source
		SysOperation.cpp
		#XMLMessage.cpp
		#xmlEventParser.cpp
	)
endif()

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (Source PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
