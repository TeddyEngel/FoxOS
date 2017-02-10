#include <cstddef>
#include <cstring>
#include <cstdio>
#include <kernel/tty.h>

#include "vga.h"

const size_t tty_manager::VGA_WIDTH = 80;
const size_t tty_manager::VGA_HEIGHT = 25;
uint16_t* const tty_manager::VGA_MEMORY = (uint16_t*) 0xB8000;
const uint8_t tty_manager::TAB_WIDTH = 4;

size_t tty_manager::_cursor_row;
size_t tty_manager::_cursor_column;
uint8_t tty_manager::_color;
uint16_t* tty_manager::_buffer;

void tty_manager::initialize(void)
{
    _cursor_row = 0;
    _cursor_column = 0;
    _color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    _buffer = VGA_MEMORY;
    clear();
}

void tty_manager::write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        putchar(data[i]);
    move_physical_cursor(_cursor_column, _cursor_row);
}

void tty_manager::write_string(const char* data)
{
    write(data, strlen(data));
}

void tty_manager::clear()
{
    for (size_t y = 0; y < VGA_HEIGHT; ++y)
        for (size_t x = 0; x < VGA_WIDTH; ++x)
            put_entry_at(' ', _color, y, x);
}

void tty_manager::move_cursor_left()
{
    if (_cursor_column == 0 && _cursor_row > 0)
    {
        _cursor_column = VGA_WIDTH - 1;
        --_cursor_row;
        return;
    }
    --_cursor_column;
    move_physical_cursor(_cursor_column, _cursor_row);
}

void tty_manager::move_cursor_right()
{

}

void tty_manager::move_cursor_up()
{

}

void tty_manager::move_cursor_down()
{

}

void tty_manager::set_color(uint8_t color)
{
    _color = color;
}

void tty_manager::put_entry_at(unsigned char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    _buffer[index] = vga_entry(c, color);
}

void tty_manager::put_entry_at_cursor(unsigned char c, uint8_t color)
{
    put_entry_at(c, color, _cursor_column, _cursor_row);
}

void tty_manager::scrolldown()
{
    // Move all lines up
    for (size_t y = 0; y < VGA_HEIGHT - 1; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            const size_t index_next_line = (y + 1) * VGA_WIDTH + x;

            _buffer[index] = _buffer[index_next_line];
        }
    }

    // Clear last line
    for (size_t x = 0; x < VGA_WIDTH; x++)
        put_entry_at(' ', _color, x, (VGA_HEIGHT - 1));
}

void tty_manager::scrolldown_if_needed()
{
    // Scrolling
    while (_cursor_row >= VGA_HEIGHT)
    {
        scrolldown();
        --_cursor_row;
    }
}

void tty_manager::putchar(char c)
{
    unsigned char uc = c;

    // Newline
    if (uc == '\n')
    {
        _cursor_column = 0;
        ++_cursor_row;
        scrolldown_if_needed();
        return;
    }
    // Backspace
    else if (uc == '\b')
    {
        move_cursor_left();
        put_entry_at_cursor(' ', _color);
        return;
    }
    // Horizontal tab
    else if (uc == '\t')
    {
        _cursor_column += TAB_WIDTH;
        if (_cursor_column >= VGA_WIDTH)
            _cursor_column = VGA_WIDTH - 1;
        return;
    }
    // Carriage return
    else if (uc == '\r')
    {
        _cursor_column = 0;
        return;
    }

    // Scrolling
    scrolldown_if_needed();
    put_entry_at_cursor(uc, _color);
    if (++_cursor_column == VGA_WIDTH) {
        _cursor_column = 0;
        if (++_cursor_row == VGA_HEIGHT)
            _cursor_row = 0;
    }
}

void tty_manager::move_physical_cursor(uint8_t column, uint8_t row)
{
    if (column >= VGA_WIDTH)
        column = VGA_WIDTH - 1;
    if (row >= VGA_HEIGHT)
        row = VGA_HEIGHT - 1;
    const size_t index = row * VGA_WIDTH + column;
    outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outb(0x3D5, index >> 8);          // Send the high cursor byte.
    outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outb(0x3D5, index);               // Send the low cursor byte.
}