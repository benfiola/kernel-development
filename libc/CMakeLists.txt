project(clibs)
message(STATUS "Building C Libraries.")

set(LIB_C_C_FLAGS "-isystem=/usr/include -O2 -g -Wall -Wextra -std=gnu11")
set(LIB_C_CPP_FLAGS "-D__is_myos_libc -Iinclude")
set(LIB_K_C_FLAGS "-isystem=/usr/include -O2 -g -Wall -Wextra -ffreestanding -fbuiltin")
set(LIB_K_CPP_FLAGS "-D__is_myos_libc -Iinclude -D__is_myos_kernel")


message(STATUS "Building hosted libc.")
set(CMAKE_C_FLAGS ${LIB_C_C_FLAGS})
set(CMAKE_CPP_FLAGS ${LIB_C_CPP_FLAGS})
file(GLOB_RECURSE LIB_C_SRC "*.c")
add_library(libc STATIC ${LIB_C_SRC})

message(STATUS "Building free-standing libk.")
set(CMAKE_C_FLAGS ${LIB_K_C_FLAGS})
set(CMAKE_CPP_FLAGS ${LIB_K_CPP_FLAGS})
file(GLOB_RECURSE LIB_K_SRC "*.c")
add_library(libk STATIC ${LIB_K_SRC})
add_dependencies(libc kernel-includes libc-includes)
add_dependencies(libk kernel-includes libc-includes)
target_compile_definitions(libc PRIVATE ${LIB_C_CPP_FLAGS})
target_compile_definitions(libk PRIVATE ${LIB_K_CPP_FLAGS})

add_custom_target(
	libc-deploy 
	COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:libc>" "${CMAKE_SYSROOT}/usr/lib/$<TARGET_FILE_NAME:libc>" 
	COMMENT "Copying libc to sysroot." 
	DEPENDS libc
)

add_custom_target(
	libk-deploy 
	COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:libk>" "${CMAKE_SYSROOT}/usr/lib/$<TARGET_FILE_NAME:libk>" 
	COMMENT "Copying libk to sysroot." 
	DEPENDS libk
)

add_custom_target(
	clibs
	DEPENDS libc libkk
)

add_custom_target(
	clibs-deploy
	DEPENDS libc-deploy libk-deploy
)