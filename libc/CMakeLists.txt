project(clibraries)
message(STATUS "Building C Libraries.")

set(LIB_C_C_FLAGS "-isystem=/usr/include -O2 -g -Wall -Wextra -std=gnu11")
set(LIB_C_CPP_FLAGS "-D__is_myos_libc -Iinclude")
set(LIB_K_C_FLAGS "-isystem=/usr/include -O2 -g -Wall -Wextra -ffreestanding -fbuiltin")
set(LIB_K_CPP_FLAGS "-D__is_myos_libc -Iinclude -D__is_myos_kernel")


message(STATUS "Building hosted libc.")
set(CMAKE_C_FLAGS ${LIB_C_C_FLAGS})
set(CMAKE_CPP_FLAGS ${LIB_C_CPP_FLAGS})
file(GLOB_RECURSE LIB_C_SRC "*.c")
add_library(c STATIC ${LIB_C_SRC})

message(STATUS "Building free-standing libk.")
set(CMAKE_C_FLAGS ${LIB_K_C_FLAGS})
set(CMAKE_CPP_FLAGS ${LIB_K_CPP_FLAGS})
file(GLOB_RECURSE LIB_K_SRC "*.c")
add_library(k STATIC ${LIB_K_SRC})

target_compile_definitions(c PRIVATE ${LIB_C_CPP_FLAGS})
target_compile_definitions(k PRIVATE ${LIB_K_CPP_FLAGS})
add_custom_command(TARGET c POST_BUILD COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:c>" "${CMAKE_SYSROOT}/usr/lib/$<TARGET_FILE_NAME:c>" COMMENT "Copying libc to sysroot.")
add_custom_command(TARGET k POST_BUILD COMMAND "${CMAKE_COMMAND}" -E copy "$<TARGET_FILE:k>" "${CMAKE_SYSROOT}/usr/lib/$<TARGET_FILE_NAME:k>" COMMENT "Copying libk to sysroot.")