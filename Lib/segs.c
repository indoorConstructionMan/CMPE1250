#include <hidef.h>     
#include "derivative.h"
#include "segs.h"

#define Segs_WLATCH PORTA &= (~0x01); PORTA |= 0x01;
#define Segs_ML PORTA &= (~0x02);
#define Segs_MH PORTA |= 0x02;

void Segs_Init (void) {
    // Set Write mode (input not loaded into memory)
    // Set load command mode (loads control word) 
    PORTA |= PORTA_PA0 | PORTA_PA1;

    // Initialize data/command ports (set direction to be outputs for 7 segs)
    DDRA |= 0x03;
    DDRB = 0xff;

    Segs_Clear();
}

// addr -> which segment to target, value -> value to be wrtten, dp -> include decimal point
void Segs_Normal (unsigned char addr, unsigned char value, Segs_DPOption dp) {
    // addr -> clear first 5 bits (keeping last 3 digits state)
    addr &= 0x07;

    // Bank A, Normal Op, Decode, Hex, No Data Coming
    addr |= 0b01011000;

    // If decimal point -> clear MSB
    // if not decimal point -> set MSB
    if (dp) {
        value &= (~0x80);
    } else {
        value |= 0x80;
    }

    // Send Command
    PORTB = addr;
    Segs_MH

    Segs_WLATCH

    // Send Data
    PORTB = value;
    Segs_ML

    Segs_WLATCH
}

void Segs_Custom (unsigned char address, unsigned char value) {
// addr -> clear first 5 bits (keeping last 3 digits state)
    address &= 0x07;

    // Bank A, Normal Op,No Decode, Hex, No Data Coming
    address |= 0b01111000;

    // Send Command
    PORTB = address;
    Segs_MH

    Segs_WLATCH

    // Send Data
    PORTB = value;
    Segs_ML

    Segs_WLATCH
}

void Segs_ClearDigit(unsigned char address) {
    // addr -> clear first 5 bits (keeping last 3 digits state)
    address &= 0x07;

    // Bank A, Normal Op,No Decode, Hex, No Data Coming
    address |= 0b01111000;

    // Send Command
    PORTB = address;
    Segs_MH

    Segs_WLATCH

    // Send Data
    PORTB = 0b10000000;
    Segs_ML

    Segs_WLATCH
}

void Segs_Clear(void) {
    int i = 0; 
    for (i = 0; i < 8; i++) {
        Segs_ClearDigit(i);
    }
}

void Segs_ClearLine(Segs_LineOption lo) {
    int i = 4;
    int loopTill = 8;
    if (lo == Segs_LineTop) {
        i = 0;
        loopTill = 4;
    } 

    for (i; i < loopTill; i++) {
        Segs_ClearDigit(i);
    }
}

// Pass hex into value, and which line you want to place it
void Segs_16H (unsigned int value, Segs_LineOption lo) {
    int i = 0;
    int loopTill = 4;
    if (lo == Segs_LineTop) {
        Segs_ClearLine(Segs_LineTop);
        for (i; i < loopTill; i++) {
            Segs_Normal(loopTill - i - 1, value & 0x000F, Segs_DP_OFF);    
            value = value >> 4;
        }
    } else {
        Segs_ClearLine(Segs_LineBottom);
        i = 4;
        loopTill = 7;
        for (loopTill; loopTill >= i; loopTill--) {
            Segs_Normal(loopTill, value & 0x000F, Segs_DP_OFF);    
            value = value >> 4;
        }
    }
}


void Segs_16D (unsigned int value, Segs_LineOption lo) {
    int i = 0;
    int loopTill = 4;

    if (lo == Segs_LineTop) {
        Segs_ClearLine(Segs_LineTop);
        for (i; i < loopTill; i++) {
            Segs_Normal(loopTill - i - 1, value % 10, Segs_DP_OFF);    
            value = value / 10;
        }
    } else {
        Segs_ClearLine(Segs_LineBottom);
        i = 4;
        loopTill = 7;
        for (loopTill; loopTill >= i; loopTill--) {
            Segs_Normal(loopTill, value % 10, Segs_DP_OFF);    
            value = value / 10;
        }
    }
}

void Segs_8H (unsigned char address, unsigned char value) {
    Segs_ClearDigit((address) % 8);
    Segs_ClearDigit((address + 1) % 8);
    Segs_Normal((address) % 8, (value & 0xF0) >> 4, Segs_DP_OFF);
    Segs_Normal((address + 1) % 8, value & 0x0F, Segs_DP_OFF);
}

void Segs_SayErr(Segs_LineOption lo) {
    if (lo == Segs_LineTop) {
        Segs_ClearLine(Segs_LineTop);
        Segs_Custom(1, 0b11001111);
        Segs_Custom(2, 0b10001100);
        Segs_Custom(3, 0b10001100);
    } else {
        Segs_ClearLine(Segs_LineBottom);
        Segs_Custom(5, 0b11001111);
        Segs_Custom(6, 0b10001100);
        Segs_Custom(7, 0b10001100);
    }
}