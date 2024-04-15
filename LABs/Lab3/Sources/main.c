/********************************************************************/
// HC12 Program:  Lab 3 : Number Entry / Hex Converter
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       A more detailed explanation of the program is entered here               
// Date:          April 14, 2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"
#include "rti.h"
#include "pll_clock.h"
#include "segs.h"
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

/********************************************************************/
// Global Variables
/********************************************************************/
int editDigit;
int decimalValue;
int swUpOld, swDownOld, swLeftOld, swRightOld;
int swUpCurr, swDownCurr, swLeftCurr, swRightCurr;
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
  //EnableInterrupts;
  
  // PLL Clock set to 20MHz
  Clock_Set20MHZ();

  // Switch/pushbuttons init
  SWL_Init();

  // RTI init
  RTI_Init();

  // Segs init
  Segs_Init();

/********************************************************************/
  // one-time initializations
/********************************************************************/
  editDigit = 3;
  decimalValue = 0;

  swUpOld = 0;
  swDownOld = 0;
  swLeftOld = 0;
  swRightOld = 0;
  swUpCurr = 0;
  swDownCurr = 0;
  swLeftCurr = 0;
  swRightCurr = 0;
/********************************************************************/
  // main program loop
/********************************************************************/
  Segs_Clear();
  for (;;)
  { 
    Segs_16DParam(decimalValue, Segs_LineTop, editDigit);
    Segs_16H(decimalValue, Segs_LineBottom);

    swLeftCurr = SWL_Pushed(SWL_LEFT);
    swRightCurr = SWL_Pushed(SWL_RIGHT);
    swUpCurr = SWL_Pushed(SWL_UP);
    swDownCurr = SWL_Pushed(SWL_DOWN);

    if ((swRightCurr != swRightOld) && swRightCurr && editDigit < 3) {
      editDigit++;
    } else if ((swLeftCurr != swLeftOld) && swLeftCurr && editDigit > 0) {
      editDigit--;
    } else if ((swUpCurr != swUpOld) && swUpCurr) {
      decimalValue = ModifyDecimalValue(decimalValue, editDigit, 1);
    } else if ((swDownCurr != swDownOld) && swDownCurr) {
      decimalValue = ModifyDecimalValue(decimalValue, editDigit, 0);
    }

    swLeftOld = swLeftCurr;
    swRightOld = swRightCurr;
    swUpOld = swUpCurr;
    swDownOld = swDownCurr;

    RTI_Delay(50);
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
