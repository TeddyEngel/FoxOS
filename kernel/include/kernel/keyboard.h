/*
** Keyboard driver
*/

#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

#include <cstdint>

#include <kernel/registers.h>

// #define DEFAULT_FREQUENCY 50

// #define PIT_DATA_PORT_CHANNEL_0 0x40 // Output connected to IRQ0
// #define PIT_DATA_PORT_CHANNEL_1 0x41 // Controls refresh rates of DRAM
// #define PIT_DATA_PORT_CHANNEL_2 0x42 // Controls the pc speaker
// #define PIT_COMMAND_PORT 0x43
// #define PIT_REPEATING_MODE 0x36 // To set the clock to repeat once it reaches 0

class keyboard_manager
{
public:
    static void initialize(uint32_t frequency);

private:
    static void on_keypress(registers_t);
};

#endif /* _KERNEL_KEYBOARD_H */