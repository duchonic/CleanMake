# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	add_library (
		Source
		logger.cpp
		serial.cpp
		SysOperation.cpp
		SingletonCollector.cpp
		OperationFactory.cpp
		ConnectionFactory.cpp
		SocketConnection.cpp
		#XMLMessage.cpp
		#xmlEventParser.cpp
	)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_library (
		Source
		logger.cpp
		serial.cpp
		SysOperation.cpp
		SingletonCollector.cpp
		OperationFactory.cpp
		ConnectionFactory.cpp
		SocketConnection.cpp
		XMLMessage.cpp
		xmlEventParser.cpp
		timer.cpp
		timeUtil.cpp
	)
else()
	add_library (
		Source
		logger.cpp
		serial.cpp
		SysOperation.cpp
		SingletonCollector.cpp
		OperationFactory.cpp
		ConnectionFactory.cpp
		SocketConnection.cpp
		#XMLMessage.cpp
		#xmlEventParser.cpp
	)
endif()



# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (Source PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
