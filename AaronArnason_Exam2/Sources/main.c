/********************************************************************/
// HC12 Program:  Lab Exam 2 - SCI/RTI/PLL
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       This program uses interrupts to generate a 1 second delay
// Date:          April 3, 2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>

#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"     /* For LED/Switch Functions */
#include "pll_clock.h"  /* Set bus speed to 20Mhz */
#include "rti.h"
#include "sci.h"
#include "misc.h"

//Other system includes or your includes go here
//#include <stdlib.h>

/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned long baudRate = 19200;
unsigned long bps;

int bufferSize = 100;
char buffer[100];

int i = 0;
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  //Any main local variables must be declared here
  // main entry point
  _DISABLE_COP();
  // Set Bus Speed
  Clock_Set20MHZ();
  // Init the Switches/LEDs
  SWL_Init();
  //EnableInterrupts;
	RTI_Init();
  // Init the SCI Module
  bps = sci0_InitMath(Clock_GetBusSpeed(), baudRate);

  // PLL
  // PLLCLOCK == 2 * 16MHZ * synr+1/refdv+1
  // BusSpeed (pass into sci module) == PLLClock / 2
  // given bus speed => multiply by 2, divide by 32 MHz gets a ratio. from that get synr and refdv (32 max value for synr and refdv)

  //RTI
  //RTICTL = 0b10010111; bit 7 => 1 (decimal)/ 0 (binary)
  //                     bit 6-4 => 16MHz / (number in column header)
  //                     bit 3-0 => (16MHz / (number in column header)) / row column

  // SCI module
  // SCI0BD = number --> BusSpeed/(16 * baudRate)

/********************************************************************/
  // one-time initializations
/********************************************************************/
  buffer[99] = '\0';
/********************************************************************/
  // main program loop
/********************************************************************/
  for (;;) {
    sci0_txStrXY(4, 4, buffer);

    for (i = 0; i < bufferSize; i++) {
      buffer[i] = sci0_bread();
      //sci0_txByte(buffer[i]);
      if (buffer[i] == 0xD) { //enter key
        sci0_txStr("\r\n");
        break;
      } 
    }
    buffer[i] = '\0';
  }

}

/********************************************************************/
// Functions
/********************************************************************/


/********************************************************************/
// Interrupt Service Routines
/********************************************************************/

