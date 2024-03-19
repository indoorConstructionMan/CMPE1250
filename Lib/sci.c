#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
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
unsigned long sci0_InitMath (unsigned long ulBusClock, unsigned long ulBaudRate){
  unsigned long denominator = ulBaudRate * 16; 
  unsigned long actualBaud = ulBusClock / (((((ulBusClock / denominator) * 10)+ 5) / 10) * 16) ;
  SCI0BD = ((((ulBusClock * 10) / denominator)+ 5) / 10);

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


/*
while(1) {
    if (*straddr == '\0') break;
    sci0_txByte(*straddr);
    straddr++;
  }
*/