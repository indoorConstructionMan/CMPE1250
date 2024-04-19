#include <hidef.h>      
#include <math.h>
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
    lcd_MacroDelay;
    // first attempt to send command

    lcd_EUp;
    lcd_RWDown;
    lcd_EDown;
    lcd_RSDown;
    lcd_MicroDelay;        
    lcd_MacroDelay;
    // second attempt to send command

    lcd_EUp;
    lcd_RWDown;
    lcd_EDown;
    lcd_RSDown;
    lcd_MicroDelay;
    lcd_MacroDelay;
    // third attempt to send command. busy flag should work now?!

    lcd_Ins(0b00111000);        // function set: 8 bits, 2 lines, 5x7 dots
    lcd_MacroDelay;

    lcd_Ins(0b00001110);        // display ON/off cursor ON/off blink on/OFF
    lcd_MacroDelay;

    lcd_Ins(0b00000001);        // clear entire display, set address to 0   
    lcd_MacroDelay;

    lcd_Ins(0b00000110);        // entry mode set: increment
    lcd_MacroDelay;
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
    while (lcd_Busy() > 0);

    lcd_RWDown;     // Writing
    lcd_RSDown;     // command

    PTH = val;

    lcd_EUp;
    lcd_MicroDelay;
    lcd_EDown;      // and latch  

    lcd_MacroDelay;
}

void lcd_Data (unsigned char val) {
    while (lcd_Busy() > 0);

    lcd_RWDown;     // Writing
    lcd_RSUp;     // data

    PTH = val;

    lcd_EUp;
    lcd_MicroDelay;
    lcd_EDown;      // and latch    

    lcd_MacroDelay;
}

void lcd_String (char const * cString) {
    while(*cString != '\0') {
        lcd_Data(*cString++);
    }
    //lcd_Data(' ');
}

void lcd_Addr (unsigned char addr) {
    addr |= 0b10000000;
    lcd_Ins(addr);
}

// ix == column, iy == line
void lcd_AddrXY (unsigned char ix, unsigned char iy) {
    unsigned char lcdPosition = 0b10000000;
    
    if (iy == 1) {
        lcdPosition |= 64;
    } else if (iy == 2) {
        lcdPosition |= 20;
    } else if (iy == 3) {
        lcdPosition |= 84;
    }

    lcdPosition += ix % 20;
    
    lcd_Ins(lcdPosition);
}

void lcd_StringXY (unsigned char ix, unsigned char iy, char const * const straddr) {
    lcd_AddrXY(ix, iy);
    lcd_String(straddr);
}

// cursor on = 1, cursor off = 0, blinkon = 1, blinkoff = 0
void lcd_DispControl (unsigned char curon, unsigned char blinkon) {
    unsigned char command = 0b00001100;
    command |= command | curon << 1 | blinkon;
    
    lcd_Ins(command);
    lcd_Ins(command);
}

void lcd_Clear (void) {
    unsigned char command = 1;
    
    lcd_Ins(command);
    lcd_Ins(command);
}

void lcd_Home (void) {
    lcd_AddrXY(0, 0);
    lcd_DispControl(1, 0);
}

void lcd_ShiftL (void) {
    lcd_Ins(0b00010000);
    //lcd_Ins(0b00011000);  shift whole display to left
}

void lcd_ShiftR (void) {
    lcd_Ins(0b00010100);
    //lcd_Ins(0b00011100); Shift whole display to right
}