/*
** Keyboard driver
*/

#ifndef _KERNEL_KEYBOARD_DRIVER_H
#define _KERNEL_KEYBOARD_DRIVER_H

#include <cstdint>

#include <kernel/registers.h>

#define KEYBOARD_DATA_BUFFER 0x60

class keyboard_driver
{
public:
    static void initialize();

private:
    static void on_keypress(registers_t);

private:
    static uint8_t kbdus[];
};

#endif /* _KERNEL_KEYBOARD_DRIVER_H */