#pragma once

#include <cstdint>

/* This will be a function in start.asm. We use this to properly
*  reload the new segment registers */
extern "C"
{
    void gdt_flush(uint32_t);
}
