/*
** Timer to handle the system clock / IRQ0
*/

#ifndef _KERNEL_TIMER_H
#define _KERNEL_TIMER_H

#include <cstdint>

#include <kernel/registers.h>

#include <kernel/pit_types.h>

class timer_manager
{
public:
    static void initialize();

private:
    static void on_tick(registers_t);

private:
    static const uint32_t FREQUENCY;

private:
    static uint32_t _tick;
};

#endif /* _KERNEL_TIMER_H */