
MESSAGE(STATUS "Building kernel")

set(KERNEL_C_FLAGS "-ffreestanding -fbuiltin -Wall -Wextra")
set(KERNEL_CPP_FLAGS "-D__is_myos_kernel -Iinclude")
set(KERNEL_LD_FLAGS "")
set(KERNEL_LIBS "-nostdlib -lk -gcc")

LOAD_PROFILE("i386")

MESSAGE(STATUS "Finding all generic sources")
FILE(GLOB_RECURSE GENERIC_SRCS "**/*.c" "**/*.s")
REMOVE_FILES_WITH_PATTERN("${GENERIC_SRCS}" "arch" "GENERIC_SRCS")
MESSAGE(STATUS ${GENERIC_SRCS})

ADD_EXECUTABLE(kernel ${PLATFORM_SRCS} ${GENERIC_SRCS})