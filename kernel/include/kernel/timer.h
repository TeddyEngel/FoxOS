/*
** Timer to handle the system clock / IRQ0
*/

#ifndef _KERNEL_TIMER_H
#define _KERNEL_TIMER_H

#include <cstdint>

#include <kernel/registers.h>

#define DEFAULT_FREQUENCY 50

#define PIT_DATA_PORT_CHANNEL_0 0x40 // Output connected to IRQ0
#define PIT_DATA_PORT_CHANNEL_1 0x41 // Controls refresh rates of DRAM
#define PIT_DATA_PORT_CHANNEL_2 0x42 // Controls the pc speaker
#define PIT_COMMAND_PORT 0x43
#define PIT_REPEATING_MODE 0x36 // To set the clock to repeat once it reaches 0

class timer_manager
{
public:
    static void initialize(uint32_t frequency);

private:
    static void on_tick(registers_t);

private:
    static uint32_t _tick;
};

#endif /* _KERNEL_TIMER_H */