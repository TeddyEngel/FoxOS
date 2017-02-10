#include <kernel/keyboard_driver.h>

#include <cstdio>

#include <kernel/isr.h>
#include <kernel/irq.h>

bool keyboard_driver::shiftPressed = false;

/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
uint8_t keyboard_driver::kbdus[256] =
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

uint8_t keyboard_driver::read_scancode()
{
    return inb(KEYBOARD_DATA_BUFFER);
}

void keyboard_driver::on_keypress(registers_t)
{
    uint8_t scancode;
    // bool shift_key_pressed = false;
    scancode = read_scancode();

    if (shiftPressed)
        printf("1:shift is pressed, scancode: %d\n", scancode);
    // else
    //     printf("shift is not pressed");

    if(scancode == KEY_LEFT_SHIFT)     
    {
      shiftPressed = true;
      puts("SHIFT DOWN\n");
      return;
    }      
    else if(scancode & KEY_SHIFT_UP_FLAG)
    {
      shiftPressed = false;
      puts("SHIFT UP\n");
    }      

    // if (shiftPressed)
    //     printf("2:shift is pressed");
    // else
    //     printf("shift is not pressed");
    // else    
    // {    

     else if (scancode & 0x80)
     {
          int shiftaltctrl = 1;//Put anything to see what special keys were pressed
          printf("SPECIAL KEY\n");
     }
     else
     {  
        if (shiftPressed)
            scancode += 128;
        printf("%d\n", scancode);
        // putchar(kbdus[scancode]);
          // printtxt(kblayout[scancode]); //Prints the character which was pressed         
     }     
    // }

    // uint8_t scancode;

    /* Read from the keyboard's data buffer */
    // scancode = inb(KEYBOARD_DATA_BUFFER);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    // if (scancode & 0x80)
    // {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
        // scancode += 128;
        // keyboard_driver::shiftPressed = true;
        // puts("SHIFT-");
    // }
    // else
    // {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        // if (keyboard_driver::shiftPressed)
        //     scancode += 128;
        // putchar(kbdus[scancode]);
    // }
}
