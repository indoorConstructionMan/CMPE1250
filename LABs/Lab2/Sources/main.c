/********************************************************************/
// HC12 Program:  Lab 2 : 16-Bit Segs Functions
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       A more detailed explanation of the program is entered here               
// Date:          April 12, 2024
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
int counter;
int dpAddress;
int hex;
int timer;
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
  counter = 0;
  dpAddress = 0;
  hex = 0;
  timer = 0;
/********************************************************************/
  // main program loop
/********************************************************************/
  Segs_Clear();
  for (;;)
  {
    RTI_Delay(50);

    // 1 second
    if (timer % 20 == 0) {
      SWL_TOG(SWL_GREEN);
      if (hex == 1) {
        Segs_16H(counter, Segs_LineTop);  
      } else if (hex == 0) {
        Segs_16D(counter, Segs_LineTop);  
      }
      
      counter++;
      Segs_ClearLine(Segs_LineBottom);
    }

    // 200ms
    if (timer % 4 == 0 && timer % 20 != 0) {
      Segs_Custom(dpAddress % 4 + 4, 0);
      dpAddress++;
      if (dpAddress == 4) dpAddress = 0;
    }
    
    timer++;

    // Already checking counter, so check if switch is pressed -> result is both same ...set counter = 0;
    if (counter > 9999 || SWL_Pushed(SWL_CTR) == 1) counter = 0;
    if (SWL_Pushed(SWL_UP) == 1) {
      hex = 1;
    } else if (SWL_Pushed(SWL_DOWN) == 1) {
      hex = 0;
    }
    SWL_TOG(SWL_RED);
  }                   
}

/*
  Frequency of RED LED -> 100 ms -> Toggles every 50 ms

  Frequency of GREEN LED -> 2 seconds -> Toggles every 1 second (1000 ms)

  Timing is essentially independant of the Delay. Meaning the programming logic to add the button pushes/zero the counter
  does not add an appreciable amount of time (it is negligible)

  The values don't deviate from IDEAL
*/

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
