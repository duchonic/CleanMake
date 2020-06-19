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
target_include_directories (Communication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(
	Collector
	SingletonCollector.cpp
)

add_library (
	Source
	SysOperation.cpp
)

add_library (
	Lightsource
	Lightsource.cpp
	LightsourceManager.cpp
)


#target_include_directories (Source PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
