/*
** "Simple" keyboard driver
**
** TODO:
** Handle caps lock
** Add dvorak mapping
** Write scancodes translated to some memory area
*/

#include <kernel/KeyboardDriver.h>

#include <cstdio>

#include <kernel/KernelManager.h>
#include <kernel/InterruptManager.h>
#include <kernel/irq_types.h>

extern KernelManager kernelManager;

/* KBDUS means US Keyboard Layout. This is a _scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
const uint8_t KeyboardDriver::MAPPING_US[] =
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

    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(',  /* 9 */
  ')', '_', '+', '\b', /* Backspace */
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

KeyboardDriver::KeyboardDriver(KernelManager& kernelManager)
    : _kernelManager(kernelManager)
    , _status(0)
    , _scancode(0)
    , _shiftPressed(false)
{
}

void KeyboardDriver::initialize()
{
    InterruptManager& interruptManager = _kernelManager.getInterruptManager();
    interruptManager.registerHandler(IRQ1, &onKeypressHook);
} 

void KeyboardDriver::enable()
{
    int32_t data = inb(0x61);
    outb(0x61, data & 0x7F);
}

void KeyboardDriver::disable()
{
    int32_t data = inb(0x61);
    outb(0x61, data | 0x80);
}

void KeyboardDriver::restart()
{    
   disable();
   enable();
}

uint8_t KeyboardDriver::readStatus()
{
    return inb(KEYBOARD_STATUS_PORT);
}

uint8_t KeyboardDriver::readScancode()
{
    return inb(KEYBOARD_SCANCODE_PORT);
}

void KeyboardDriver::showLightIfNeeded()
{
    // TODO: Implement
    // 0xED using the described method, then you send the byte that says which lights are to be on or off. 
    // This byte has the following format: Bit0 is Scroll lock, Bit1 is Num lock, and Bit2 is Caps lock. 
}

void KeyboardDriver::onKeypress()
{
    _status = readStatus();
    _scancode = readScancode();

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
            kernelManager.getTtyManager().moveCursorLeft();
            return;
        }
        else if (_scancode == RGHT)
        {
            kernelManager.getTtyManager().moveCursorRight();
            return;
        }
        else if (_scancode == UP)
        {
            kernelManager.getTtyManager().moveCursorUp();
            return;
        }
        else if (_scancode == DOWN)
        {
            kernelManager.getTtyManager().moveCursorDown();
            return;
        }
        if (_shiftPressed == true)
            _scancode += SHIFT_MODIFIER;
        putchar(MAPPING_US[_scancode]);
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

void KeyboardDriver::onKeypressHook(registers_t)
{
    KeyboardDriver& keyboardDriver = kernelManager.getKeyboardDriver();
    keyboardDriver.onKeypress();
}