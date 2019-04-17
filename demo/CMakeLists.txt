# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable (demo demo.cpp)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo

if (WIN32)
    message(STATUS "add windows libraries")
	if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
		target_link_libraries (
			demo 
			LINK_PUBLIC 
			Source 
			CustomLib
			"C:/cLibs/xmlwrapp/lib/xmlwrapp.lib"
			#wsock32 
			ws2_32
		)
	else()
		target_link_libraries (
			demo 
			LINK_PUBLIC 
			Source 
			CustomLib
			"C:/cLibs/xmlwrapp/lib/xmlwrapp.lib"
			#wsock32 
			ws2_32
		)
	endif()
else()
	target_link_libraries (
		demo 
		LINK_PUBLIC 
		Source 
		CustomLib
	)
endif()


