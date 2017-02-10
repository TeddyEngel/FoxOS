/*
** Keyboard driver
*/

#ifndef _KERNEL_KEYBOARD_DRIVER_H
#define _KERNEL_KEYBOARD_DRIVER_H

#include <cstdint>

#include <kernel/registers.h>

#define KEYBOARD_DATA_BUFFER 0x60
#define KEY_LEFT_SHIFT 0x2A
#define KEY_SHIFT_UP_FLAG 0xAA

class keyboard_driver
{
public:
    static void initialize();
    static void enable();
    static void disable();
    static void restart();

private:
    static uint8_t read_scancode();
    static void on_keypress(registers_t);

private:
    static bool shiftPressed;
    static uint8_t kbdus[];
};

#endif /* _KERNEL_KEYBOARD_DRIVER_H */