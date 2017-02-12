#include <kernel/TtyManager.h>

#include <cstddef>
#include <cstring>
#include <cstdio>

#include <kernel/KernelManager.h>

#include "vga.h"

const size_t TtyManager::VGA_WIDTH = 80;
const size_t TtyManager::VGA_HEIGHT = 25;
uint16_t* const TtyManager::VGA_MEMORY = (uint16_t*) 0xB8000;
const uint8_t TtyManager::TAB_WIDTH = 4;

TtyManager::TtyManager(KernelManager& kernelManager)
    : _kernelManager(kernelManager)
    , _cursor_row(0)
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
    movePhysicalCursor(_cursor_column, _cursor_row);
}

void TtyManager::writeString(const char* data)
{
    write(data, strlen(data));
}

void TtyManager::clear()
{
    for (size_t y = 0; y < VGA_HEIGHT; ++y)
        for (size_t x = 0; x < VGA_WIDTH; ++x)
            putEntryAt(' ', _color, y, x);
}

void TtyManager::moveCursorLeft()
{
    if (_cursor_column == 0 && _cursor_row > 0)
    {
        _cursor_column = VGA_WIDTH - 1;
        --_cursor_row;
    }
    else if (_cursor_column == 0 && _cursor_row == 0)
    {
        scrollUp();
        _cursor_column = VGA_WIDTH - 1;
    }
    else
        --_cursor_column;
    movePhysicalCursor(_cursor_column, _cursor_row);
}

void TtyManager::moveCursorRight()
{
    if (_cursor_column == VGA_WIDTH - 1 && _cursor_row < VGA_HEIGHT - 1)
    {
        _cursor_column = 0;
        ++_cursor_row;
    }
    else if (_cursor_column == VGA_WIDTH - 1 && _cursor_row == VGA_HEIGHT - 1)
    {
        scrollDown();
        _cursor_column = 0;
    }
    else
        ++_cursor_column;
    movePhysicalCursor(_cursor_column, _cursor_row);
}

void TtyManager::moveCursorUp()
{
    if (_cursor_row == 0)
        scrollUp();
    else
        --_cursor_row;
    movePhysicalCursor(_cursor_column, _cursor_row);
}

void TtyManager::moveCursorDown()
{
    if (_cursor_row == VGA_HEIGHT - 1)
        scrollDown();
    else
        ++_cursor_row;
    movePhysicalCursor(_cursor_column, _cursor_row);
}

void TtyManager::setColor(uint8_t color)
{
    _color = color;
}

void TtyManager::putEntryAt(unsigned char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    _buffer[index] = vga_entry(c, color);
}

void TtyManager::putEntryAtCursor(unsigned char c, uint8_t color)
{
    putEntryAt(c, color, _cursor_column, _cursor_row);
}

void TtyManager::scrollUp()
{
    // TODO: Fill the top line with history line
    // For now we just clear the first line
    for (size_t x = 0; x < VGA_WIDTH; x++)
        putEntryAt(' ', _color, x, 0);

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

void TtyManager::scrollDown()
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
        putEntryAt(' ', _color, x, (VGA_HEIGHT - 1));
}

void TtyManager::putchar(char c)
{
    unsigned char uc = c;

    // Newline
    if (uc == '\n')
    {
        moveCursorNewLine();
        return;
    }
    // Backspace
    else if (uc == '\b')
    {
        moveCursorLeft();
        putEntryAtCursor(' ', _color);
        return;
    }
    // Horizontal tab
    else if (uc == '\t')
    {
        int i = 0;

        while (i++ < TAB_WIDTH)
            moveCursorRight();
        return;
    }
    // Carriage return
    else if (uc == '\r')
    {
        moveCursorBeginLine();
        return;
    }

    putEntryAtCursor(uc, _color);
    moveCursorRight();
}

void TtyManager::movePhysicalCursor(uint8_t column, uint8_t row)
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

void TtyManager::moveCursorNewLine()
{
    if (_cursor_row == VGA_HEIGHT - 1)
        scrollDown();
    else
        ++_cursor_row;
    _cursor_column = 0;
    movePhysicalCursor(_cursor_column, _cursor_row);
}

void TtyManager::moveCursorBeginLine()
{
    _cursor_column = 0;
}