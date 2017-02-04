#include <cstddef>
#include <cstring>
#include <cstdio>
#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_cursor_row;
static size_t terminal_cursor_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void)
{
    terminal_cursor_row = 0;
    terminal_cursor_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;
    terminal_clear();
}

void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putentryatcursor(unsigned char c, uint8_t color)
{
    terminal_putentryat(c, color, terminal_cursor_column, terminal_cursor_row);
}

void terminal_scrolldown()
{
    // Move all lines up
    for (size_t y = 0; y < VGA_HEIGHT - 1; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            const size_t index_next_line = (y + 1) * VGA_WIDTH + x;

            terminal_buffer[index] = terminal_buffer[index_next_line];
        }
    }

    // Clear last line
    for (size_t x = 0; x < VGA_WIDTH; x++)
        terminal_putentryat(' ', terminal_color, x, (VGA_HEIGHT - 1));
}

void terminal_putchar(char c)
{
    unsigned char uc = c;

    // Newline
    if (uc == '\n')
    {
        terminal_cursor_column = 0;
        ++terminal_cursor_row;
        terminal_movecursor(terminal_cursor_column, terminal_cursor_row);
        return;
    }
    // Backspace
    else if (uc == '\b')
    {
        if (terminal_cursor_column == 0 && terminal_cursor_row > 0)
        {
            terminal_cursor_column = VGA_WIDTH - 1;
            --terminal_cursor_row;
        }
        else if (terminal_cursor_column > 0)
            --terminal_cursor_column;
        terminal_movecursor(terminal_cursor_column, terminal_cursor_row);
        terminal_putentryatcursor(' ', terminal_color);
        return;
    }
    // Horizontal tab
    else if (uc == '\t')
    {
        terminal_cursor_column += 4;
        if (terminal_cursor_column >= VGA_WIDTH)
            terminal_cursor_column = VGA_WIDTH - 1;
        terminal_movecursor(terminal_cursor_column, terminal_cursor_row);
        return;
    }
    // Carriage return
    else if (uc == '\r')
    {
        terminal_cursor_column = 0;
        terminal_movecursor(terminal_cursor_column, terminal_cursor_row);
        return;
    }
    // Scrolling
    while (terminal_cursor_row >= VGA_HEIGHT)
    {
        terminal_scrolldown();
        --terminal_cursor_row;
        terminal_movecursor(terminal_cursor_column, terminal_cursor_row);
    }
    terminal_putentryatcursor(uc, terminal_color);
    if (++terminal_cursor_column == VGA_WIDTH) {
        terminal_cursor_column = 0;
        if (++terminal_cursor_row == VGA_HEIGHT)
            terminal_cursor_row = 0;
    }
    terminal_movecursor(terminal_cursor_column, terminal_cursor_row);
}

void terminal_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
    terminal_write(data, strlen(data));
}

void terminal_movecursor(uint8_t x, uint8_t y)
{
    if (x >= VGA_WIDTH)
        x = VGA_WIDTH - 1;
    if (y >= VGA_HEIGHT)
        y = VGA_HEIGHT - 1;
    const size_t index = y * VGA_WIDTH + x;
    outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outb(0x3D5, index >> 8);          // Send the high cursor byte.
    outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outb(0x3D5, index);               // Send the low cursor byte.
}

void terminal_clear()
{
    for (size_t y = 0; y < VGA_HEIGHT; ++y)
        for (size_t x = 0; x < VGA_WIDTH; ++x)
            terminal_putentryat(' ', terminal_color, y, x);
}
