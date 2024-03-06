/********************************************************************/
// HC12 Program:  ICA07 - Interrupt driven delay and button press
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       This program uses interrupts to generate a 1 second delay
// Date:          March 6, 2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"     /* For LED/Switch Functions */
#include "pll_clock.h"  /* Set bus speed to 20Mhz */
#include "rti.h"        /* For the rtiMasterCount, RTI_INIT(), RTI_Delay_ms*/
//Other system includes or your includes go here
//#include <stdlib.h>
//#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

//#define PART1
//#define PART2
#define PART3
/********************************************************************/
// Local Prototypes
/********************************************************************/
// RTI interrupt prototype
interrupt VectorNumber_Vrti void Vrti_ISR(void);

/********************************************************************/
// Global Variables
/********************************************************************/
volatile unsigned long rtiMasterCount = 0;
int toggleMilliseconds = 10;
int priority = 0;
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
  // RTI init method
  RTI_Init();
  // Init the Switches/LEDs
  SWL_Init();
  //EnableInterrupts;
	EnableInterrupts;

/********************************************************************/
  // one-time initializations
/********************************************************************/

/********************************************************************/
  // main program loop
/********************************************************************/
  #ifdef PART1
    // Part 1: 
    for (;;) 
    {
      if (GetSwitchPushedCount() == 1) {
        if (SWL_Pushed(SWL_UP) == 1) {
          toggleMilliseconds = 8;
        }

        if (SWL_Pushed(SWL_DOWN) == 1) {
          toggleMilliseconds = 12;
        }
      }

      SWL_TOG(SWL_RED);
      RTI_Delay_ms(toggleMilliseconds); 
    }
  #endif

  #ifdef PART2
    // Part 2: 
    for (;;)
    { 
      while(SWL_Pushed(SWL_LEFT) == 1) {
        SWL_ON(SWL_RED);
        RTI_Delay_ms(1); 
        SWL_OFF(SWL_RED);
        RTI_Delay_ms(9); 
      }

      if (GetSwitchPushedCount() == 1) {
        if (SWL_Pushed(SWL_UP) == 1) {
          toggleMilliseconds = 8;
        }

        if (SWL_Pushed(SWL_DOWN) == 1) {
          toggleMilliseconds = 12;
        }
      }

      SWL_TOG(SWL_RED);
      RTI_Delay_ms(toggleMilliseconds); 
    }                 
  #endif

  #ifdef PART3
    //Part 3: 
    for (;;)
    { 
      while(SWL_Pushed(SWL_RIGHT) == 1 && priority == 1) { 
        SWL_OFF(SWL_RED);
        SWL_ON(SWL_GREEN); 
      }

      while(SWL_Pushed(SWL_LEFT) == 1) {
        SWL_ON(SWL_RED);
        RTI_Delay_ms(1); 
        SWL_OFF(SWL_RED);
        RTI_Delay_ms(9); 
        if (priority == 1) break;
      }

      if (GetSwitchPushedCount() == 1) {
        if (SWL_Pushed(SWL_UP) == 1) {
          toggleMilliseconds = 8;
        }

        if (SWL_Pushed(SWL_DOWN) == 1) {
          toggleMilliseconds = 12;
        }
      }

      SWL_TOG(SWL_RED);
      RTI_Delay_ms(toggleMilliseconds); 
    }        
  #endif         
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
interrupt VectorNumber_Vrti void Vrti_ISR(void)
{
  CRGFLG = CRGFLG_RTIF_MASK; //clear flag;
  //Perform some action here
  if(SWL_Pushed(SWL_RIGHT) == 1) {
    priority = 1;
  }  else {
    priority = 0;
    SWL_OFF(SWL_GREEN);
  }
  rtiMasterCount++;
}