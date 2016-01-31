project(kernel)

message(STATUS "Building kernel.")

set(KERNEL_C_FLAGS "-isystem=/usr/include -O2 -g -ffreestanding -fbuiltin -Wall -Wextra")
set(KERNEL_CPP_FLAGS "-D__is_myos_kernel -Iinclude")
set(KERNEL_LINKER_FLAGS "-T arch/i386/linker.ld -nostdlib -lk -lgcc")

set(CMAKE_C_FLAGS ${KERNEL_C_FLAGS})

file(GLOB_RECURSE KERNEL_SRC "*.c" "*.s")
# these need to go in front and back of the list, respectively
file(GLOB_RECURSE CRTI_SRC "*crti.s")
file(GLOB_RECURSE CRTN_SRC "*crtn.s")
set(CRTBEGIN_O "/home/benfiola/opt/cross/lib/gcc/i686-elf/5.2.0/crtbegin.o")
set(CRTEND_O "/home/benfiola/opt/cross/lib/gcc/i686-elf/5.2.0/crtend.o")
list(REMOVE_ITEM KERNEL_SRC ${CRTI_SRC})
list(REMOVE_ITEM KERNEL_SRC ${CRTN_SRC})

add_executable(myos.kernel ${CRTI_SRC} ${CRTBEGIN_O} ${KERNEL_SRC} ${CRTEND_O} ${CRTN_SRC})
target_compile_definitions(myos.kernel PRIVATE ${KERNEL_CPP_FLAGS})
SET_TARGET_PROPERTIES(myos.kernel PROPERTIES LINK_FLAGS ${KERNEL_LINKER_FLAGS})