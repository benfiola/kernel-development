cmake_minimum_required(VERSION 3.0.0)
project(myos C ASM-ATT)

# this won't work
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
SET(CMAKE_STATIC_LIBRARY_PREFIX "")
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

add_custom_target(
	clean-all
	COMMAND make clean
	COMMAND rm -rf ./sysroot
	COMMAND rm -rf ./iso
	COMMAND rm -rf ./cdrom
	VERBATIM
)

set(GRUB_FLAGS "")
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(GRUB_FLAGS "-d /usr/lib/grub/i386-pc/")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
message(status ${GRUB_FLAGS})
add_custom_target(
	iso
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:myos.kernel> "${CMAKE_SYSROOT}/iso/boot/$<TARGET_FILE_NAME:myos.kernel>"
	COMMAND ${CMAKE_COMMAND} -E copy grub/grub.cfg "${CMAKE_SYSROOT}/iso/boot/grub/grub.cfg"
	COMMAND mkdir -p ${CMAKE_SYSROOT}/cdrom
	COMMAND grub-mkrescue -d /usr/lib/grub/i386-pc/ -o ${CMAKE_SYSROOT}/cdrom/myos.iso ${CMAKE_SYSROOT}/iso
	DEPENDS myos.kernel
	VERBATIM
)

add_custom_target(
	qemu
	COMMAND qemu-system-i386 -cdrom ${CMAKE_SYSROOT}/cdrom/myos.iso
	DEPENDS iso
	VERBATIM
)

