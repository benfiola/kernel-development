# we force this because otherwise CMake attempts to test compile and that fails
INCLUDE(CMakeForceCompiler)

# this one is important
SET(CMAKE_SYSTEM_NAME Linux)

#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
# we force this because otherwise CMake attempts to test compile and that fails
CMAKE_FORCE_C_COMPILER(i686-elf-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(i686-elf-g++ GNU)

# set ar and as tools
set(CMAKE_AR "i686-elf-ar")
set(CMAKE_ASM-ATT_COMPILER "i686-elf-as")

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /home/benfiola/opt/cross)

# set our sysroot
SET(CMAKE_SYSROOT "${CMAKE_SOURCE_DIR}/sysroot")

# search for programs in the build host directories
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)