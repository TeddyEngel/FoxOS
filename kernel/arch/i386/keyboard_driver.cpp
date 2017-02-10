/*
** "Simple" keyboard driver
**
** TODO:
** Handle caps lock
** Handle arrows
** Add dvorak mapping
*/

#include <kernel/keyboard_driver.h>

#include <cstdio>

#include <kernel/isr.h>
#include <kernel/irq.h>
#include <kernel/tty.h>

uint8_t keyboard_driver::_status = 0;
uint8_t keyboard_driver::_scancode = 0;
bool keyboard_driver::_shiftPressed = false;

/* KBDUS means US Keyboard Layout. This is a _scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
uint8_t keyboard_driver::_kbdus[256] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '-', '=', '\b', /* Backspace */
  '\t',         /* Tab */
  'q', 'w', 'e', 'r',   /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,          /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 '\'', '`',   0,        /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',            /* 49 */
  'm', ',', '.', '/',   0,              /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */

    /* Buffer keys */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    /* End of buffer keys */

    0,  '!', '@', '#', '$', '%', '^', '&', '*', '(', /* 9 */
  ')', '_', '_', '+', '\b', /* Backspace */
  '\t',         /* Tab */
  'Q', 'W', 'E', 'R',   /* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /* Enter key */
    0,          /* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
 '\"', '~',   0,        /* Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',            /* 49 */
  'M', '<', '>', '?',   0,              /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};  

void keyboard_driver::initialize()
{
    isr_manager::register_handler(IRQ1, &on_keypress);
} 

void keyboard_driver::enable()
{
    int32_t data = inb(0x61);
    outb(0x61, data & 0x7F);
}

void keyboard_driver::disable()
{
    int32_t data = inb(0x61);
    outb(0x61, data | 0x80);
}

void keyboard_driver::restart()
{    
   disable();
   enable();
}

uint8_t keyboard_driver::read_status()
{
    return inb(KEYBOARD_STATUS_PORT);
}

uint8_t keyboard_driver::read_scancode()
{
    return inb(KEYBOARD_SCANCODE_PORT);
}

void keyboard_driver::show_light_if_needed()
{
    // TODO: Implement
    // 0xED using the described method, then you send the byte that says which lights are to be on or off. 
    // This byte has the following format: Bit0 is Scroll lock, Bit1 is Num lock, and Bit2 is Caps lock. 
}

void keyboard_driver::on_keypress(registers_t)
{
    _status = read_status();
    _scancode = read_scancode();

    // When the key is down
    if(!(_scancode & 0x80))
    {
        // Handle special keys
        if(_scancode == SHFT)     
        {
            _shiftPressed = true;
            return;
        }
        else if (_scancode == LEFT)
        {
            tty_manager::move_cursor_left();
            return;
        }
        if (_shiftPressed == true)
            _scancode += 128;
        putchar(_kbdus[_scancode]);
    }
    // When the key is back up
    else
    {
        if(_scancode == SHFT + KEY_UP_DECAL)     
        {
            _shiftPressed = false;
            return;
        }   
    }
}
