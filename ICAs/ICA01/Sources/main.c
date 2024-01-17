/********************************************************************/
// HC12 Program:  ICA01 - LED Blink Program
// Processor:     MC9S12XDP512
// Bus Speed:     MHz
// Author:        Aaron Arnason
// Details:       This program blinks a RED LED on and off ad infinitum
// Date:          January 12, 2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
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

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned int counter, index;
/********************************************************************/
// Constants
/********************************************************************/
#define RED_LED 0b10000000
#define INDEX_MAX 10

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
  PT1AD1 |= RED_LED;
  DDR1AD1 |= RED_LED;
  counter = 0;
  index = 0;

/********************************************************************/
  // main program loop
/********************************************************************/
  for (;;)
  {
    if(++counter == 0)  
    {
      if(++index >= INDEX_MAX)
      {
        index = 0;
        PT1AD1 ^= RED_LED;
      }
    }
  }                 
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/