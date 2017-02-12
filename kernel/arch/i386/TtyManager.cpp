#include <kernel/TtyManager.h>

#include <cstddef>
#include <cstring>
#include <cstdio>

#include "vga.h"

const size_t TtyManager::VGA_WIDTH = 80;
const size_t TtyManager::VGA_HEIGHT = 25;
uint16_t* const TtyManager::VGA_MEMORY = (uint16_t*) 0xB8000;
const uint8_t TtyManager::TAB_WIDTH = 4;

TtyManager::TtyManager()
    : _cursor_row(0)
    , _cursor_column(0)
    , _color(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK))
    , _buffer(VGA_MEMORY)
{

}

void TtyManager::initialize(void)
{
    clear();
}

void TtyManager::write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        putchar(data[i]);
    move_physical_cursor(_cursor_column, _cursor_row);
}

void TtyManager::write_string(const char* data)
{
    write(data, strlen(data));
}

void TtyManager::clear()
{
    for (size_t y = 0; y < VGA_HEIGHT; ++y)
        for (size_t x = 0; x < VGA_WIDTH; ++x)
            put_entry_at(' ', _color, y, x);
}

void TtyManager::move_cursor_left()
{
    if (_cursor_column == 0 && _cursor_row > 0)
    {
        _cursor_column = VGA_WIDTH - 1;
        --_cursor_row;
    }
    else if (_cursor_column == 0 && _cursor_row == 0)
    {
        scrollup();
        _cursor_column = VGA_WIDTH - 1;
    }
    else
    {
        --_cursor_column;
    }
    move_physical_cursor(_cursor_column, _cursor_row);
}

void TtyManager::move_cursor_right()
{
    if (_cursor_column == VGA_WIDTH - 1 && _cursor_row < VGA_HEIGHT - 1)
    {
        _cursor_column = 0;
        ++_cursor_row;
    }
    else if (_cursor_column == VGA_WIDTH - 1 && _cursor_row == VGA_HEIGHT - 1)
    {
        scrolldown();
        _cursor_column = 0;
    }
    else
    {
        ++_cursor_column;
    }
    move_physical_cursor(_cursor_column, _cursor_row);
}

void TtyManager::move_cursor_up()
{
    if (_cursor_row == 0)
        scrollup();
    else
        --_cursor_row;
    move_physical_cursor(_cursor_column, _cursor_row);
}

void TtyManager::move_cursor_down()
{
    if (_cursor_row == VGA_HEIGHT - 1)
        scrolldown();
    else
        ++_cursor_row;
    move_physical_cursor(_cursor_column, _cursor_row);
}

void TtyManager::set_color(uint8_t color)
{
    _color = color;
}

void TtyManager::put_entry_at(unsigned char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    _buffer[index] = vga_entry(c, color);
}

void TtyManager::put_entry_at_cursor(unsigned char c, uint8_t color)
{
    put_entry_at(c, color, _cursor_column, _cursor_row);
}

void TtyManager::scrollup()
{
    // TODO: Fill the top line with history line
    // For now we just clear the first line
    for (size_t x = 0; x < VGA_WIDTH; x++)
        put_entry_at(' ', _color, x, 0);

    // Move all lines down
    for (size_t y = VGA_HEIGHT - 1; y >= 1; --y)
    {
        for (size_t x = 0; x < VGA_WIDTH; ++x)
        {
            const size_t index = y * VGA_WIDTH + x;
            const size_t index_previous_line = (y - 1) * VGA_WIDTH + x;

            _buffer[index] = _buffer[index_previous_line];
        }
    }
}

void TtyManager::scrolldown()
{
    // Move all lines up
    for (size_t y = 0; y < VGA_HEIGHT - 1; ++y)
    {
        for (size_t x = 0; x < VGA_WIDTH; ++x)
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

void TtyManager::putchar(char c)
{
    unsigned char uc = c;

    // Newline
    if (uc == '\n')
    {
        move_cursor_newline();
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
        int i = 0;

        while (i++ < TAB_WIDTH)
            move_cursor_right();
        return;
    }
    // Carriage return
    else if (uc == '\r')
    {
        move_cursor_beginline();
        return;
    }

    put_entry_at_cursor(uc, _color);
    move_cursor_right();
}

void TtyManager::move_physical_cursor(uint8_t column, uint8_t row)
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

void TtyManager::move_cursor_newline()
{
    if (_cursor_row == VGA_HEIGHT - 1)
        scrolldown();
    else
        ++_cursor_row;
    _cursor_column = 0;
    move_physical_cursor(_cursor_column, _cursor_row);
}

void TtyManager::move_cursor_beginline()
{
    _cursor_column = 0;
}