add_library (
	CustomLib
	helper.cpp
	timer.cpp
	timeUtil.cpp
)
target_include_directories (CustomLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
