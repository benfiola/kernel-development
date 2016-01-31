project(kernel)

message(STATUS "Building kernel.")

set(KERNEL_C_FLAGS "-isystem=/usr/include -O2 -g -ffreestanding -fbuiltin -Wall -Wextra")
set(KERNEL_CPP_FLAGS "-D__is_myos_kernel -Iinclude")
set(KERNEL_LINKER_FLAGS "-T arch/i386/linker.ld -nostdlib")

set(CMAKE_C_FLAGS ${KERNEL_C_FLAGS})

file(GLOB_RECURSE SRC_FILES "*.s" "*.c" )

# these are important files that we need to control ordering on.  during linking
# the order should be crti crtbegin <objects> kernel crtend crtn
# here we just define the particular exclusions
file(GLOB_RECURSE CRTI_SRC "*crti.s")
file(GLOB_RECURSE CRTN_SRC "*crtn.s")
file(GLOB_RECURSE KERNEL_SRC "*kernel.c")

# remove these files from our src collection
set(FILES_TO_REMOVE "")
list(APPEND FILES_TO_REMOVE ${CRTI_SRC})
list(APPEND FILES_TO_REMOVE ${CRTN_SRC})
list(APPEND FILES_TO_REMOVE ${KERNEL_SRC})
foreach(FILE ${FILES_TO_REMOVE})
	list(REMOVE_ITEM SRC_FILES ${FILE})
endforeach(FILE ${LINK_PRE_OBJS})

# we just want to compile these files, not link them
add_library(crti OBJECT ${CRTI_SRC})
add_library(crtn OBJECT ${CRTN_SRC})
add_library(kernel OBJECT ${KERNEL_SRC})

# now we collect our objects for linkage by either referencing them directly
# or constructing their path from what we know
set(CRTBEGIN_O "/home/benfiola/opt/cross/lib/gcc/i686-elf/5.2.0/crtbegin.o")
set(CRTEND_O "/home/benfiola/opt/cross/lib/gcc/i686-elf/5.2.0/crtend.o")
file(RELATIVE_PATH CRTI_REL_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CRTI_SRC})
file(RELATIVE_PATH CRTN_REL_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CRTN_SRC})
file(RELATIVE_PATH KERNEL_REL_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${KERNEL_SRC})
set(CRTI_O ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/crti.dir/${CRTI_REL_PATH}.o)
set(CRTN_O ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/crtn.dir/${CRTN_REL_PATH}.o)
set(KERNEL_O ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/kernel.dir/${KERNEL_REL_PATH}.o)

# build strings to modify our linking command
set(LINK_PRE_OBJS "")
set(LINK_POST_OBJS "")
string(CONCAT LINK_PRE_OBJS "${CRTI_O} ${CRTBEGIN_O}")
string(CONCAT LINK_POST_OBJS "${KERNEL_O} ${CRTEND_O} ${CRTN_O}")

# this is where our link order is defined
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <FLAGS> ${LINK_PRE_OBJS} <OBJECTS> ${LINK_POST_OBJS} -o <TARGET> <LINK_LIBRARIES>")

# now we define the thing we want to build
add_executable(myos.kernel ${SRC_FILES})

# this is dependent upon our clibs being built and sent to the sysroot, as well as the files we're manually building
add_dependencies(myos.kernel clibs-deploy crti crtn kernel)
target_compile_definitions(myos.kernel PRIVATE ${KERNEL_CPP_FLAGS})

# we want -lk and -lgcc args when we link
target_link_libraries(myos.kernel libk gcc)

# set our linker flags here
set_target_properties(myos.kernel PROPERTIES LINK_FLAGS ${KERNEL_LINKER_FLAGS})