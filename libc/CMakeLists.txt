MESSAGE(STATUS "Building libc")

set(LIBC_C_FLAGS "-Wall -Wextra")
set(LIBC_CPP_FLAGS "-D__is_myos_libc -Iinclude")
set(LIBK_C_FLAGS "-ffreestanding -fbuiltin")
set(LIBK_CPP_FLAGS "-D__is_myos_kernel")

LOAD_PROFILE("i386")

