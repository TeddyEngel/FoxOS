FoxOS is a simple operating system with a c++ kernel

Prerequisites
-------------

On MacOSX:
1- Start by installing homebrew
2- Run: brew install homebrew/dupes/make --with-default-names
3- Run: brew install libmpc
4- Install GRUB: http://wiki.osdev.org/GRUB
5- Install objconv
6- Run: brew install xorriso

To configure:
-------------

1- Edit config.sh

To build:
---------

1- Run headers.sh
2- Run build.sh

To test on qemu:
---------------

1- After building, run qemu.sh

To clean:
---------

1- Run clean.sh
