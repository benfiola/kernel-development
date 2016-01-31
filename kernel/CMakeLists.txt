project(kernel)

message(STATUS "Building kernel.")

set(KERNEL_C_FLAGS "-isystem=/usr/include -O2 -g -ffreestanding -fbuiltin -Wall -Wextra -Iinclude")
set(KERNEL_CPP_FLAGS "-D__is_myos_kernel -Iinclude")
set(KERNEL_LINKER_FLAGS "-T arch/i386/linker.ld -nostdlib")

set(CMAKE_C_FLAGS ${KERNEL_C_FLAGS})

file(GLOB_RECURSE KERNEL_SRC "*.c" "*.s")

# ordering is crti crtbegin files crtend crtn at LINK time.
# crtbegin and crtend are part of the cross compiler, so we need to pull them in externally.
# this whole process is needlessly difficult (but then again, this use case is rare)
# first we find the crti/crtn files
file(GLOB_RECURSE CRTI_SRC "*crti.s")
file(GLOB_RECURSE CRTN_SRC "*crtn.s")
# we then find our crtbegin and crtend files - need to make this more...dynamic
set(CRTBEGIN_O "/home/benfiola/opt/cross/lib/gcc/i686-elf/5.2.0/crtbegin.o")
set(CRTEND_O "/home/benfiola/opt/cross/lib/gcc/i686-elf/5.2.0/crtend.o")
# get rid of the crti and crtn files from our source store (because we're building 'em separately)
list(REMOVE_ITEM KERNEL_SRC ${CRTI_SRC})
list(REMOVE_ITEM KERNEL_SRC ${CRTN_SRC})
# yep.  this is how you compile them.  just compile them - no linking or anything.
add_library(crti OBJECT ${CRTI_SRC})
add_library(crtn OBJECT ${CRTN_SRC})
# this is where it starts to get wonky.  we're building the path to our built .o files for crti and crtn
# there are generator expressions for this, BUT they don't work when you...
file(RELATIVE_PATH CRTI_REL_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CRTI_SRC})
file(RELATIVE_PATH CRTN_REL_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CRTN_SRC})
set(CRTI_O ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/crti.dir/${CRTI_REL_PATH}.o)
set(CRTN_O ${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/crtn.dir/${CRTN_REL_PATH}.o)

# ...when you MANUALLY specify linking order here!  if we had generator expressions working, this would be
# pretty easy, still kludge-y though.  this works reliably enough for now, but i'm annoyed that this is the best i can do.
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <FLAGS> ${CRTI_O} ${CRTBEGIN_O} <OBJECTS> ${CRTEND_O} ${CRTN_O} -o <TARGET> <LINK_LIBRARIES>")
add_executable(myos.kernel ${KERNEL_SRC})
add_dependencies(myos.kernel crti crtn)
target_compile_definitions(myos.kernel PRIVATE ${KERNEL_CPP_FLAGS})
target_link_libraries(myos.kernel k)
set_target_properties(myos.kernel PROPERTIES LINK_FLAGS ${KERNEL_LINKER_FLAGS})

# now let's copy it to the sysroot
add_custom_command(
	TARGET myos.kernel
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:myos.kernel> "${CMAKE_SYSROOT}/boot/$<TARGET_FILE_NAME:myos.kernel>"
	COMMENT "Moving over the built kernel"
	DEPENDS myos.kernel
)