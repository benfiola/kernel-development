project(libc-include)

message(STATUS "Building libc-includes")

file(GLOB_RECURSE HEADER_FILES "*.h")
set(SYSROOT_INCLUDES "")
foreach(HEADER_FILE ${HEADER_FILES})
	file(RELATIVE_PATH REL_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${HEADER_FILE})
	add_custom_command(
		OUTPUT "${CMAKE_SYSROOT}/usr/include/${REL_PATH}"
		COMMAND ${CMAKE_COMMAND} -E copy "${HEADER_FILE}" "${CMAKE_SYSROOT}/usr/include/${REL_PATH}"
		DEPENDS "${HEADER_FILE}"
	)
	list(APPEND SYSROOT_INCLUDES "${CMAKE_SYSROOT}/usr/include/${REL_PATH}")
endforeach(HEADER_FILE ${HEADER_FILES})
add_custom_target(libc-includes ALL DEPENDS ${SYSROOT_INCLUDES})