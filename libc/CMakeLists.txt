MESSAGE(STATUS "Building libc")

# here we set flags specific for libc
set(LIBC_C_FLAGS "-Wall -Wextra")
set(LIBC_CPP_FLAGS "-D__is_myos_libc -Iinclude")
set(LIBK_C_FLAGS "-ffreestanding -fbuiltin")
set(LIBK_CPP_FLAGS "-D__is_myos_kernel")

LOAD_PROFILE("i386")

MESSAGE(STATUS "including directories")
INCLUDE_DIRECTORIES(include)

MESSAGE(STATUS "Finding all generic sources")
FILE(GLOB_RECURSE GENERIC_SRCS "**/*.c" "**/*.s")
REMOVE_FILES_WITH_PATTERN("${GENERIC_SRCS}" "arch" "GENERIC_SRCS")
MESSAGE(STATUS ${GENERIC_SRCS})

SET(CMAKE_C_FLAGS "${GENERAL_C_FLAGS} ${LIBC_C_FLAGS} ${PLATFORM_C_FLAGS}")
ADD_DEFINITIONS("${GENERAL_CPP_FLAGS} ${LIBC_CPP_FLAGS} ${PLATFORM_CPP_FLAGS}")
ADD_EXECUTABLE(libc ${PLATFORM_SRCS} ${GENERIC_SRCS})

