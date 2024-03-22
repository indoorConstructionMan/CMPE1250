#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include <stdio.h>
#include "sci.h"


void sci0_Init(void){
  // Set baud rate using 20 mhz bus
  SCI0BD = 130;

  // Enable TX/RX of SCI module
  SCI0CR2 |= SCI0CR2_RE_MASK | SCI0CR2_TE_MASK;
}

// Using the pre calculated valuse for baud rate. Struct defined in .h file.
void sci0_InitEnum(BaudRate br){
  SCI0BD = br;

  // Enable TX/RX of SCI module
  SCI0CR2 |= SCI0CR2_RE_MASK | SCI0CR2_TE_MASK;
}

// Programmatic implementation including rounding.
unsigned long sci0_InitMath(unsigned long ulBusClock, unsigned long ulBaudRate){
  unsigned long denominator = ulBaudRate * 16; 
  unsigned long actualBaud = ulBusClock / (((((ulBusClock / denominator) * 10)+ 5) / 10) * 16) ;
  
  SCI0BD = ((((ulBusClock * 10) / denominator)+ 5) / 10) & 0x1FFF;

  // Enable TX/RX of SCI module
  SCI0CR2 |= SCI0CR2_RE_MASK | SCI0CR2_TE_MASK;

  return actualBaud;
}

// non-blocking read
int sci0_read(unsigned char * pData){
    if(SCI0SR1_RDRF) {
      *pData = SCI0DRL;
      return 1;
    }
    return 0;
}

// Blocking Read
unsigned char sci0_bread(void){
  while (!SCI0SR1_RDRF) {}
  return SCI0DRL;
}

// blocking transmit
void sci0_txByte (unsigned char data) {
  while (!SCI0SR1_TDRE) {}
  SCI0DRL = data;
}

// Transmit an entire string
void sci0_txStr(char const * straddr) {
  int i = 0;
  while(*(straddr + i) != '\0') {
    sci0_txByte(*(straddr + i));
    i++;
  }
}

// not tested
int sci0_Peek(void) {
  if (SCI0SR1 & SCI0SR1_RDRF_MASK) return 1;
  return 0;
}

// 0 and 1 are the same row/col
// Tested and works
void sci0_GoToXY(int iRow, int iCol) {
  char sendCursor[20];
  if (sprintf(sendCursor, "\x1b[%u;%uH", iRow, iCol)) {
    sci0_txStr(sendCursor);
  }
}

// Tested and works
void sci0_txStrXY(int iRow, int iCol, char const * straddr) {
  sci0_GoToXY(iRow, iCol);
  sci0_txStr(straddr);
}

// Erases display
void sci0_ClearScreen(void) {
  sci0_txStr("\x1b[2J");
}

// Tested works
void sci0_ShowBin16(unsigned int iVal) {
  int i = 0;
  char binaryString[17];
  binaryString[16] = '\0';
  for (i = 0; i < 16; i++) {
    if (iVal & 1 > 0) {
      binaryString[15-i] = '1';
    } else {
      binaryString[15-i] = '0';
    }
    iVal = iVal >> 1;
  }
  sci0_txStr(binaryString);
}


void sci0_drawStaticData(void) {
  sci0_txStrXY(1, 2, "Aaron Arnason - Lab 1 CMPE 1250");
  sci0_txStrXY(2, 2, "Simple Binary Calculator");
  sci0_txStrXY(5, 5, "OP A:        (     )");
  sci0_txStrXY(6, 5, "OP B:        (     )");
  sci0_txStrXY(10, 10, "-----------------");
}


void sci0_DrawState(unsigned int iOPA, unsigned int iOPB, operation op) {
  sci0_txStrXY(5, 11, "0x1234");
  sci0_txStrXY(5, 19, "04660");
  sci0_txStrXY(6, 11, "0xABCD");
  sci0_txStrXY(6, 19, "43981");
  sci0_txStrXY(8, 11, "0001001000110100");
  sci0_txStrXY(9, 11, "1010101111001101");
  sci0_txStrXY(11, 11, "0000001000000100");
  sci0_DrawOperator(op);
  sci0_GoToXY(5, 13);
}

void sci0_DrawOperator(operation op) {
  if (op == AND_OPERATION) sci0_txStrXY(9, 9, "&");
  if (op == OR_OPERATION) sci0_txStrXY(9, 9, "|");
}