/*
** "Simple" keyboard driver
**
** TODO: Handle caps lock
** TODO: Write scancodes translated to some memory area
** TODO: Once I have heap mem, add mappings dynamically
*/

#include <kernel/KeyboardDriver.h>

#include <cstdio>

#include <kernel/KernelManager.h>
#include <kernel/InterruptManager.h>
#include <kernel/irq_types.h>

extern KernelManager kernelManager;

// Keyboard mappings
#include <kernel/KeyboardMappingEnUs.h>
extern const uint8_t KeyboardMappingEnUs[KEYS_COUNT];
#include <kernel/KeyboardMappingDvorak.h>
extern const uint8_t KeyboardMappingDvorak[KEYS_COUNT];

const char* KeyboardDriver::SERVICE_NAME = "Keyboard Driver";

KeyboardDriver::KeyboardDriver(KernelManager& kernelManager)
    : _kernelManager(kernelManager)
    , _status(0)
    , _scancode(0)
    , _shiftPressed(false)
    , _currentMappingIndex(0)
{
    registerMapping(MAPPING_EN_US, KeyboardMappingEnUs);
    registerMapping(MAPPING_DVORAK, KeyboardMappingDvorak);
    setActiveMapping(MAPPING_DVORAK); // Hardcoded for now
}

int KeyboardDriver::initialize()
{
    InterruptManager& interruptManager = _kernelManager.getInterruptManager();
    interruptManager.registerHandler(IRQ1, &onKeypressHook);
    return 0;
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

void KeyboardDriver::registerMapping(uint8_t index, const uint8_t mapping[KEYS_COUNT])
{
    if (index > MAPPING_COUNT)
        return;
    for (int i = 0; i < KEYS_COUNT; ++i)
        _mappings[index][i] = mapping[i];
}

void KeyboardDriver::setActiveMapping(uint8_t index)
{
    if (index > MAPPING_COUNT)
        return;
    _currentMappingIndex = index;
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
        putchar(_mappings[_currentMappingIndex][_scancode]);
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