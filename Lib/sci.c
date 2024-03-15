#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "pll_clock.h"
#include "sw_led.h"
#include "sci.h"
#include "misc.h"


void sci0_Init(void){
  /*long busSpeed = Clock_GetBusSpeed();
  long denominator = 9600 * 16; 

  long roundedBaudRate = busSpeed / denominator;
  SCI0BD = roundedBaudRate;
*/
  // Set baud rate using 20 mhz bus
  SCI0BD = 130;

  // Enable TX/RX of SCI module
  SCI0CR2 |= SCI0CR2_RE_MASK | SCI0CR2_TE_MASK;
}

// non-blocking read
int sci0_read(unsigned char * pData){
    if(SCI0SR1_RDRF) {
      *pData = SCI0DRL;
      return 1;
    }
    return 0;
}



// blocking transmit
void sci0_txByte (unsigned char data) {
  while (!SCI0SR1_TDRE) {}
  SCI0DRL = data;
}