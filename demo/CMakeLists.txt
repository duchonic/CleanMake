# Add executable called "demo" that is built from the source files "demo.cpp"
# The extensions are automatically found.
add_executable (demo demo.cpp)

# Link the executable to the libraries. Since the Hello library has
# public include directories we will use those link directories when building
# demo

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
		message(STATUS "Add windows libraries mingw")
		target_link_libraries (
			demo
			Factory
			Source
			Communication
			Collector
			CustomLib
			wsock32
			ws2_32
			"C:/cLibs/xmlwrapp/lib/xmlwrapp.lib"
		)
	endif()

else()
	target_link_libraries (
		demo
		LINK_PUBLIC
		Factory
		CustomLib
		Communication
		Collector
	)
endif()
