cmake_minimum_required(VERSION 3.0.0)
project(myos C ASM-ATT)

# this won't work
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

# enable assembly
enable_language(ASM-ATT)

# let's find include directories for all header files - we want to move these to the sysroot first
# since all compilation depends on them
SET(INCLUDE_DIRECTORIES "")
file(GLOB_RECURSE HEADER_FILES "*.h")
foreach(HEADER_FILE ${HEADER_FILES})
	string(REGEX MATCH ".*/include" INCLUDE_DIRECTORY "${HEADER_FILE}")
	list(FIND INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORY} FOUND)
	if(${FOUND} EQUAL -1)
		if(EXISTS ${INCLUDE_DIRECTORY}/CMakeLists.txt) 
			list(APPEND INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORY})
			add_subdirectory(${INCLUDE_DIRECTORY})
		endif(EXISTS ${INCLUDE_DIRECTORY}/CMakeLists.txt)
	endif(${FOUND} EQUAL -1)
endforeach(HEADER_FILE)

add_subdirectory(libc)
add_subdirectory(kernel)