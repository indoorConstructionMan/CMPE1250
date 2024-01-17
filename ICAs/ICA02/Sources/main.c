/********************************************************************/
// HC12 Program:  ICA02 - Convert C# to C
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Aaron Arnason
// Details:       Red light is on when green light is not, Red light 
//                is on 3x longer than green light.               
// Date:          January 17, 2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros  */
#include "derivative.h" /* derivative-specific definitions */

//Other system includes or your includes go here
//#include <stdlib.h>
//#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
void RED (unsigned int bOn);
void GREEN(unsigned int bOn);

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned int uiMainLoopCount = 0;
/********************************************************************/
// Constants
/********************************************************************/
const int comparisonValue = 0x1000;
/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  //Any main local variables must be declared here

  // main entry point
  _DISABLE_COP();
  //EnableInterrupts;
  
/********************************************************************/
  // one-time initializations
/********************************************************************/
// set lights to be off
  PT1AD1 &= 0x1F;

// set lights to be output
  DDR1AD1 = 0xE0;

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    ++uiMainLoopCount;
    RED(uiMainLoopCount);
    GREEN(uiMainLoopCount);
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
// depending on comparison value, turn red led on or off
void RED(unsigned int bOn) {
  if (bOn < comparisonValue) 
  {
    // turn red led on
    PT1AD1 |= (byte)(((unsigned long)1 << (7)));
  }
  else
  {
    // turn red led off
    PT1AD1 &= 0x7F;
  }
}

// depending on comparison value, turn green led on or off
void GREEN(unsigned int bOn) {
  if (bOn >= comparisonValue)
  {
    // turn green led on
    PT1AD1 |= 0x20;
  }
  else
  {
    // turn green led off
    PT1AD1 &= 0b11011111;
  }
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
