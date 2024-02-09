/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     MHz
// Author:        This B. You
// Details:       A more detailed explanation of the program is entered here               
// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes



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
int count = 0;
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
  
  // Part 1
  // for (;;)
  // {
  //   if (SWL_Pushed(SWL_LEFT)) {
  //     SWL_ON(SWL_RED);  
  //   } else {
  //     SWL_OFF(SWL_RED);
  //   }
    
  //   if (SWL_Pushed(SWL_CTR)) {
  //     SWL_ON(SWL_YELLOW);  
  //   } else {
  //     SWL_OFF(SWL_YELLOW);
  //   }

  //   if (SWL_Pushed(SWL_RIGHT)) {
  //     SWL_ON(SWL_GREEN);  
  //   } else {
  //     SWL_OFF(SWL_GREEN);
  //   }
  // }        

  // Part 2
  // for (;;)
  // {
  //   if (SWL_Pushed(SWL_LEFT)) {
  //     SWL_ON(SWL_RED);  
  //   } 
    
  //   if (SWL_Pushed(SWL_CTR)) {
  //     SWL_ON(SWL_YELLOW);  
  //   } 

  //   if (SWL_Pushed(SWL_RIGHT)) {
  //     SWL_ON(SWL_GREEN);  
  //   } 

  //   if (SWL_Pushed(SWL_UP)) {
  //     SWL_OFF(SWL_RED);
  //     SWL_OFF(SWL_GREEN);
  //     SWL_OFF(SWL_YELLOW);
  //   }
    
  //   if (SWL_Pushed(SWL_DOWN)) {
  //     SWL_OFF(SWL_RED);
  //     SWL_OFF(SWL_GREEN);
  //     SWL_OFF(SWL_YELLOW);
  //   }

  // }

  for (;;) 
  {
    count = GetLedCount();

    if (SWL_Pushed(SWL_LEFT)) {      
      if (count >= 2) {
        if (PT1AD1 & SWL_RED) {
          SWL_TOG(SWL_RED);
          count--;
        }
      } 
      else if (count < 2){
        SWL_TOG(SWL_RED);  
        count++;
      }
    } 
    
    if (SWL_Pushed(SWL_CTR)) {
     if (count >= 2) {
        if (PT1AD1 & SWL_YELLOW) {
          SWL_TOG(SWL_YELLOW);
          count--;
        }
      } 
      else if (count < 2) {
        SWL_TOG(SWL_YELLOW);  
        count++;
      }
    }    

    if (SWL_Pushed(SWL_RIGHT)) {
      if (count >= 2) {
        if (PT1AD1 & SWL_GREEN) {
          SWL_TOG(SWL_GREEN);
          count--;
        }
      }
      
      else if (count < 2) {
        SWL_TOG(SWL_GREEN);  
        count++;
      }
    } 

    if (SWL_Pushed(SWL_UP)) {
      SWL_OFF(SWL_RED);
      SWL_OFF(SWL_GREEN);
      SWL_OFF(SWL_YELLOW);
      count = 0;
    }
    
    if (SWL_Pushed(SWL_DOWN)) {
      SWL_OFF(SWL_RED);
      SWL_OFF(SWL_GREEN);
      SWL_OFF(SWL_YELLOW);
      count = 0;
    }

  }

}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
