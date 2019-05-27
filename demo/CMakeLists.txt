# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable (demo demo.cpp)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo

if (WIN32)
	message(STATUS "Search Windows libraries")

	if (MSVC)
		message(STATUS "Visual studio")
		find_library(WSOCK32_LIBRARY wsock32)
		find_library(WS2_32_LIBRARY ws2_32)
		message(STATUS "Add windows libraries")

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
			"${PROJECT_SOURCE_DIR}/winLibs/debug/libz-static.lib"
			"${PROJECT_SOURCE_DIR}/winLibs/debug/xmlwrapp.lib"
		)
	else()
		target_link_libraries (
			demo
			LINK_PUBLIC
			Source
			Factory
			CustomLib
			Communication
			Collector
			"C:/cLibs/xmlwrapp/lib/xmlwrapp.lib"
			wsock32
			ws2_32
		)
	endif()

else()
	target_link_libraries (
		demo
		LINK_PUBLIC
		Source
		Factory
		CustomLib
		Communication
		Collector
	)
endif()
