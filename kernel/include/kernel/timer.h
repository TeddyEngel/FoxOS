/*
** Timer to handle the system clock / IRQ0
*/

#ifndef _KERNEL_TIMER_H
#define _KERNEL_TIMER_H

#include <cstdint>

#include <kernel/registers.h>

#include <kernel/pit_types.h>

#define DEFAULT_FREQUENCY 50

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