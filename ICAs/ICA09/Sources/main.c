/********************************************************************/
// HC12 Program:  ICA08 - SCI library
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       This program uses interrupts to generate a 1 second delay
// Date:          March 13, 2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"     /* For LED/Switch Functions */
#include "pll_clock.h"  /* Set bus speed to 20Mhz */
#include "rti.h"
#include "sci.h"
#include "misc.h"

//Other system includes or your includes go here
//#include <stdlib.h>
//#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
// RTI interrupt prototype


/********************************************************************/
// Global Variables
/********************************************************************/

/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  //Any main local variables must be declared here
  unsigned char data = 'A';
  // main entry point
  _DISABLE_COP();
  // Set Bus Speed
  Clock_Set20MHZ();
  // Init the Switches/LEDs
  SWL_Init();
  //EnableInterrupts;
	RTI_Init();
  // Init the SCI Module
  sci0_Init();

/********************************************************************/
  // one-time initializations
/********************************************************************/

/********************************************************************/
  // main program loop
/********************************************************************/
  for (;;) {
    if (Clock_GetBusSpeed() == 20000000L) {
      SWL_ON(SWL_ANY);
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/

