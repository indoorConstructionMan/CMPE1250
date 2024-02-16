/********************************************************************/
// HC12 Program:  Lab Exam 1
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Aaron Arnason
// Details:       A more detailed explanation of the program is entered here               
// Date:          February 16, 2024
// Revision History :
//    ***Check Lib folder sw_led.h/sw_led.c for functions used
//    
//
/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"
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
long blockingVariableOn = 2552L;
long blockingVariableOff = 851L;



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
/********************************************************************/
  // one-time initializations
/********************************************************************/
  SWL_Init();

/********************************************************************/
  // main program loop
/********************************************************************/
// preparation
  // for (;;) {
  //   SWL_ON(SWL_ALL);
    
  // }

  // Part A
  // for (;;) {
  //   OnOffDutyCycle(SWL_RED, blockingVariableOn, blockingVariableOff);
  // }


  // Part B:
  blockingVariableOn = 2551L;
  blockingVariableOff = 850L;
  for (;;) {
    if (GetSwitchPushedCount() == 2) {
      SWL_OFF(SWL_YELLOW);
      SWL_ON(SWL_GREEN);
    } else {
      SWL_OFF(SWL_GREEN);
      SWL_ON(SWL_YELLOW);
    }
    OnOffDutyCycle(SWL_RED, blockingVariableOn, blockingVariableOff);
  }
              
}

/********************************************************************/
// Functions
/********************************************************************/

