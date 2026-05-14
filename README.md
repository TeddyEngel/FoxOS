# 🦊 FoxOS
A simple, educational operating system with a C++ kernel targeting x86 architecture.
[![License](https://img.shields.io/badge/license-BSD--2--Clause-blue.svg)](LICENCE)

<!-- Add these when you set them up:
[![Build Status](https://img.shields.io/github/actions/workflow/status/TeddyEngel/FoxOS/build.yml?branch=master)](https://github.com/TeddyEngel/FoxOS/actions)
[![Discord](https://img.shields.io/discord/YOUR_SERVER_ID?logo=discord&label=Discord)](YOUR_INVITE_LINK)
-->

## About
FoxOS is a hobby operating system built from scratch in C++ for learning low-level systems programming. It implements core OS concepts including memory management, interrupt handling, and hardware drivers while maintaining a clean, modular architecture.
The project serves as a practical exploration of operating system fundamentals—from bootloader to userspace—with readable, well-structured code.

<!-- Uncomment when you have a screenshot:

## Screenshot
![FoxOS running in QEMU](screenshot.png)
-->

## Features

### Core Kernel

- **x86 32-bit Protected Mode** — Runs in protected mode with Multiboot-compliant bootloader
- **Memory Segmentation** — GDT with Ring 0 (kernel) and Ring 3 (user) privilege levels
- **Interrupt Handling** — Full IDT with 256 interrupt/exception handlers and PIC remapping

### Memory Management

- **Virtual Memory** — Paging with 4KB pages (1024 entries per table, 1024 tables per directory)
- **Page Fault Handling** — Dynamic frame allocation and deallocation
- **Kernel Heap** — malloc/free implementation with expandable heap (up to 16MB)

### Hardware Support

- **Keyboard Driver** — Full keyboard input with EN-US and Dvorak layouts
- **VGA Terminal** — 80×25 text mode display with color support
- **System Timer** — Programmable Interval Timer (PIT) for system clock

### C++ Runtime

- **Custom Operators** — Kernel-specific `new`/`delete` implementations
- **Standard Library** — Freestanding libc and libc++ (stdio, string, memory, collections)
- **Global Constructors** — Full C++ static initialization support

  

## Architecture

### Directory Structure

| Directory | Purpose |
|-----------|---------|
| `kernel/` | Core kernel implementation |
| `kernel/arch/i386/` | x86-specific code (boot, GDT, IDT, paging, drivers) |
| `kernel/kernel/` | Main entry point (`kernel.cpp`) |
| `kernel/include/` | Public kernel headers |
| `libc/` | Freestanding C standard library |
| `libc++/` | C++ standard library (memory, collections, I/O) |

### Key Components

| Component | File | Description |
|-----------|------|-------------|
| Boot | `boot.asm` | Multiboot entry point, stack setup |
| GDT Manager | `GdtManager.cpp` | Memory segmentation, privilege rings |
| IDT Manager | `InterruptManager.cpp` | Interrupt/exception handling |
| Paging Manager | `PagingManager.cpp` | Virtual memory, 4KB pages |
| Memory Heap | `MemoryHeap.cpp` | Kernel malloc/free |
| Keyboard Driver | `KeyboardDriver.cpp` | Keyboard input (US, Dvorak) |
| TTY Manager | `TtyManager.cpp` | VGA text mode output |
| Timer Manager | `TimerManager.cpp` | System clock (PIT) |

### Build Scripts

| Script | Purpose |
|--------|---------|
| `config.sh` | Build environment configuration |
| `headers.sh` | Install headers to sysroot |
| `build.sh` | Compile kernel and libraries |
| `iso.sh` | Create bootable ISO |
| `qemu.sh` | Launch in QEMU emulator |

### Component Hierarchy

The kernel uses a modular manager-based architecture:
1. **GRUB** loads the kernel via Multiboot
2. **KernelManager** orchestrates all subsystems
3. **Core managers** (GDT, IDT, Paging) handle CPU/memory setup
4. **Hardware drivers** (Keyboard, Timer, TTY) interface with devices
5. **libc/libc++** provide runtime support

## Prerequisites

### macOS

```bash

# Install Homebrew (if not already installed)

/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install build dependencies

brew install make
brew install gmp mpfr libmpc
brew install xorriso
brew install qemu

# Install i686-elf cross-compiler toolchain

brew install i686-elf-gcc

# Install GRUB for creating bootable images


# See: https://wiki.osdev.org/GRUB

#Installing_GRUB_2_on_OS_X

Linux (Debian/Ubuntu)
sudo apt update
sudo apt install build-essential bison flex libgmp-dev libmpc-dev libmpfr-dev texinfo
sudo apt install xorriso grub-pc-bin qemu-system-x86

# Build cross-compiler toolchain


# See: https://wiki.osdev.org/GCC_Cross-Compiler

Building

# Clone the repository

git clone https://github.com/TeddyEngel/FoxOS.git
cd FoxOS

# Configure build environment (edit config.sh if needed)

./config.sh

# Install headers

./headers.sh

# Build the kernel and libraries

./build.sh

# Create bootable ISO

./iso.sh
Running
QEMU (Recommended)

# Build and run in one step

./build_and_run.sh

# Or run manually after building

./qemu.sh
Bochs

# Edit bochsrc.txt to configure Bochs settings

./bochs.sh
VirtualBox / VMware
1. Build the ISO with ./iso.sh
2. Create a new VM (Other/Unknown 32-bit)
3. Allocate at least 32MB RAM
4. Mount FoxOS.iso as the CD/DVD drive
5. Boot the VM
Contributing
Contributions are welcome! Feel free to:
- Report bugs or suggest features via Issues (https://github.com/TeddyEngel/FoxOS/issues)
- Submit pull requests for improvements
- Improve documentation
Resources
- OSDev Wiki (https://wiki.osdev.org/) — Comprehensive OS development resource
- Intel Software Developer Manuals (https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html) — x86 architecture reference
- James Molloy's Kernel Tutorial (http://www.jamesmolloy.co.uk/tutorial_html/) — Classic kernel development guide

License
This project is licensed under the BSD 2-Clause License. See LICENCE (LICENCE) for details.

```

<div align="center">
*Built with curiosity and caffeine*
</div>
