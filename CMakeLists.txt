# declare our functions at the top
FUNCTION(LOAD_PROFILE PLATFORM)
	MESSAGE(STATUS "Loading platform ${platform}")

	MESSAGE(STATUS "Finding all platform specific sources")
	FILE(GLOB_RECURSE PLATFORM_SRCS "arch/${PLATFORM}/**/*.c" "arch/${PLATFORM}/**/*.s")
	MESSAGE(STATUS ${PLATFORM_SRCS})

	MESSAGE(STATUS "Including platform specific flags")
	INCLUDE("arch/${PLATFORM}/flags.cmake")
  	SET(PLATFORM_SRCS ${PLATFORM_SRCS} PARENT_SCOPE)
ENDFUNCTION(LOAD_PROFILE)

FUNCTION(REMOVE_FILES_WITH_PATTERN FILE_LIST FILE_PATTERN VAR_NAME)
	foreach (FILE ${FILE_LIST})
    	if ("${FILE}" MATCHES "(.*)${FILE_PATTERN}(.*)")
    		list (REMOVE_ITEM FILE_LIST ${FILE})
    	endif ("${FILE}" MATCHES "(.*)${FILE_PATTERN}(.*)")
	endforeach(FILE ${FILE_LIST})
	SET(${VAR_NAME} ${FILE_LIST} PARENT_SCOPE)
ENDFUNCTION(REMOVE_FILES_WITH_PATTERN)

FUNCTION(ARCH_FROM_HOST HOST)
	set(RETURN "${HOST}")
	if ("${HOST}" MATCHES "i[0-9]+86-.*")
		set(RETURN "i386")
	endif("${HOST}" MATCHES "i[0-9]+86-.*")
	set(ARCH "${RETURN}" PARENT_SCOPE)
ENDFUNCTION(ARCH_FROM_HOST)

FUNCTION(DEFINE_TOOLCHAIN_FROM_HOST HOST)
	#apparently sysroot is not a flag - it needs to be passed right next to the invocation of gcc
	set(CMAKE_C_COMPILER "${HOST}-gcc" PARENT_SCOPE)
	set(CMAKE_AR "${HOST}-ar" PARENT_SCOPE)
	set(CMAKE_ASM-ATT_COMPILER "${HOST}-as" PARENT_SCOPE)
	SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "" PARENT_SCOPE)
ENDFUNCTION(DEFINE_TOOLCHAIN_FROM_HOST)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

# define our default host and arch
set(HOST "i686-elf")
ARCH_FROM_HOST(${HOST})

# define CC, AR, AS executables
DEFINE_TOOLCHAIN_FROM_HOST(${HOST})

# define our directories relative to the sysroot (which should be ./sysroot)
set(BOOT_DIR "/boot")
set(USER_DIR "/usr")
set(LIB_DIR "${USER_DIR}/lib")
set(INCLUDE_DIR "${USER_DIR}/include")

# define our general flags for linking, loading, preprocessing and compiling
set(GENERAL_C_FLAGS "--sysroot=${CMAKE_CURRENT_SOURCE_DIR}/sysroot -isystem=${INCLUDE_DIR} -O2 -g")
set(GENERAL_CPP_FLAGS "")
set(GENERAL_LD_FLAGS "")
set(GENERAL_LIBS "")

# enable at&t assembly support
ENABLE_LANGUAGE(ASM-ATT)

# build libc first - kernel depends on it
ADD_SUBDIRECTORY(libc)

# now build the kernel
ADD_SUBDIRECTORY(kernel)
