#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/myos.kernel isodir/boot/myos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "myos" {
	multiboot /boot/myos.kernel
}
EOF

#okay, so i built GRUB2 on Mac OS X specifically for the i386-elf target.
#GRUB2 comes with Kubuntu and is built for several targets, so I have to specify
#which one I'd like to use (I think).
OS=$(uname -s)
GRUB_FLAGS=""
if [ $OS = "Linux" ]
then
	GRUB_FLAGS="-d /usr/lib/grub/i386-pc/"
fi
grub-mkrescue $GRUB_FLAGS -o myos.iso isodir
