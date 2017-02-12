#pragma once

#include <kernel/registers.h>

extern "C"
{
    void irq_handler(registers_t);
}
