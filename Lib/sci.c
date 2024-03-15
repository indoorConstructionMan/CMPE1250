#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "pll_clock.h"
#include "sci.h"


unsigned void sci0_Init(void){
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

// blocking read
int sci0_read(unsigned char * pData){
    if(SCI0SR1_RDRF) {
      SWL_ON(SWL_GREEN);
      *pData = SCI0DRL;
      return 1;
    }
    return 0;
}