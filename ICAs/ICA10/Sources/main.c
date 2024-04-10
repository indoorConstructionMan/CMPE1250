/********************************************************************/
// HC12 Program:  ICA10 - 7 Segment Displays
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       A more detailed explanation of the program is entered here               
// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "segs.h"
#include "sw_led.h"
#include "rti.h"
#include "pll_clock.h"

//Other system includes or your includes go here
//#include <stdlib.h>
//#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/
//#define tier1
//#define tier2
#define tier3
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
// T1
unsigned int value = 0;

// T2
unsigned int loopCount = 0;
unsigned int caretPosition = 0;
unsigned int delayInMs = 100;
unsigned int numberOfTimesChanged = 0;

// T3
unsigned int held = 0;
unsigned int myCaretArray[6] = {0b10000001, 0b10001000, 0b10000010, 0b11000000, 0b10100000, 0b10010000};
unsigned int caretIndex = 0;
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
  // Init pll
  Clock_Set20MHZ();

  // Initialize the seven segment display
  Segs_Init();

  // Initialize the switch library
  SWL_Init();

  // Initialize the RTI for use of Delay (blocking)
  RTI_Init();

  

  #ifdef tier1
  value = 0xFFFF;
  Segs_8H(7, 0xE4);
  Segs_Normal(4, '3', Segs_DP_OFF);
  Segs_Custom(1, 0b01001010);
  Segs_Custom(2, 0b11110000);
  Segs_Custom(5, 0b10001011);
  Segs_Custom(6, 0b10110001);
/********************************************************************/
  // main program loop
/********************************************************************/
  
  for (;;) 
  {
    if (SWL_Pushed(SWL_CTR) == 1) {  
      Segs_16H(~value, Segs_LineTop);
      Segs_16H(value, Segs_LineBottom);
      value -= 1;
    }

    // In place of PIT delay
    RTI_Delay(100);
  }
  #endif

  #ifdef tier2
  Segs_16H(numberOfTimesChanged, Segs_LineBottom);
  for (;;) 
  {
    Segs_Custom(caretPosition, myCaretArray[caretIndex%6]);
    
    if (caretIndex % 10 == 0) {
      if (SWL_Pushed(SWL_RIGHT) == 1) {
        Segs_ClearDigit(caretPosition);
        if (caretPosition != 3) {
          caretPosition++;
          numberOfTimesChanged++;
          Segs_16H(numberOfTimesChanged, Segs_LineBottom);
        }
      } else if (SWL_Pushed(SWL_LEFT) == 1) {
        Segs_ClearDigit(caretPosition);
        if (caretPosition != 0) {
          caretPosition--;  
          numberOfTimesChanged++;
          Segs_16H(numberOfTimesChanged, Segs_LineBottom);
        }
      }
    }
    
    loopCount++;
    RTI_Delay(delayInMs);
    caretIndex++;
  }
  #endif

  #ifdef tier3
  Segs_16H(numberOfTimesChanged, Segs_LineBottom);
  for (;;) 
  {
    // Every loop, draw the carret in myCaretArray at caretIndex, at Caret Position
    Segs_Custom(caretPosition, myCaretArray[caretIndex%6]);
    
    // every 10 loops, check if held has been incremented 10 times
    if (caretIndex % 10 == 0 && held >= 10) {

      // If switch right is pushed, move caret position if it hasnt' reached the edge
      if (SWL_Pushed(SWL_RIGHT) == 1) {
        Segs_ClearDigit(caretPosition);
        if (caretPosition != 3) {
          caretPosition++;
          numberOfTimesChanged++;
          Segs_16H(numberOfTimesChanged, Segs_LineBottom);
        }
      } 

      // If switch left is pushed, move caret position if it hasnt' reached the edge
      else if (SWL_Pushed(SWL_LEFT) == 1) {
        Segs_ClearDigit(caretPosition);
        if (caretPosition != 0) {
          caretPosition--;  
          numberOfTimesChanged++;
          Segs_16H(numberOfTimesChanged, Segs_LineBottom);
        }
      }

      // If a button pressed resulted in the caret moving, then reset the held variable to 1.
      held = 1;
    } 
    
    // if the caret is not divisible by 10, check if the button is pressed.
    // if it is, then increment the held variable. If no button is pressed,
    // then reset the held variable to 1.
    else {
      if (SWL_Pushed(SWL_LEFT) == 1) {
        held++;
      } else if (SWL_Pushed(SWL_RIGHT) == 1) {
        held++;
      } else {
        held = 1;
      }
    }
    
    loopCount++;
    RTI_Delay(delayInMs);
    caretIndex++;
  }
  #endif
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
