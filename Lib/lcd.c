#include <hidef.h>      
#include "derivative.h" 
#include "lcd.h"

void lcd_Init (void) {
    PTH = 0;        // Make sure busy flag isn't set.
    
    lcd_RWDown;
    lcd_EDown;
    lcd_RSDown;     

    DDRK |= 0b00000111;     // activate control lines
    lcd_MicroDelay;         // apparently needs a delay.
    // Initialize

    PTH = 0b00111000;       // function set of commands, data 8-bit, lines 2, font 5x8 matrix
    
    lcd_EUp;
    lcd_RWDown;
    lcd_EDown;
    lcd_RSDown;
    lcd_MicroDelay;       
    // first attempt to send command

    lcd_EUp;
    lcd_RWDown;
    lcd_EDown;
    lcd_RSDown;
    lcd_MicroDelay;        
    // second attempt to send command

    lcd_EUp;
    lcd_RWDown;
    lcd_EDown;
    lcd_RSDown;
    lcd_MicroDelay;
    // third attempt to send command. busy flag should work now?!

    lcd_Ins(0b00111000);        // function set: 8 bits, 2 lines, 5x7 dots
    lcd_Ins(0b00001111);        // display on/off ctl: increment,display shift,cursor blink
    lcd_Ins(0b00000001);        // clear entire display, set address to 0   
    //lcd_Ins(0b00000110);        // entry mode set: increment
}

char lcd_Busy (void) {
    lcd_RWUp;
    lcd_EUp;

    lcd_RWDown;
    lcd_EDown;
    lcd_RSDown;

    return PTH & 0b10000000;
}

void lcd_Ins (unsigned char val) {
    while (lcd_Busy());

    lcd_RWDown;     // Writing
    lcd_RSDown;     // command

    PTH = val;

    lcd_EUp;
    lcd_MicroDelay;
    lcd_EDown;      // and latch
}

void lcd_Data (unsigned char val) {
    while (lcd_Busy());

    lcd_RWDown;     // Writing
    lcd_RSUp;     // data

    PTH = val;

    lcd_EUp;
    lcd_MicroDelay;
    lcd_EDown;      // and latch

}

void lcd_String (char const * cString) {
    while(*cString != '\0') {
        lcd_Data(*cString++);
    }
}

void lcd_Addr (unsigned char addr) {
    addr |= 0b10000000;
    lcd_Ins(addr);
}