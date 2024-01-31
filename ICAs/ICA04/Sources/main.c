/********************************************************************/
// HC12 Program:  ICA04 - GPIOs and LEDs
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Aaron Arnason
// Details:       A more detailed explanation of the program is entered here               
// Date:          January 31, 2024
// Revision History :
// 
//
// Part 1: Because the RED LED is turning on and off so fast it appears to
//         be on at all times (in reality it is less bright then if it were
//         just turned on). It's frequency is greater than the frequency
//         the human eye can detect.
//
//
//
//
//
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
#define RED_LED 0b10000000
/********************************************************************/
// Local Prototypes
/********************************************************************/
void ToggleRed(void);
void Trap(long value);
void Trap1(void);

/********************************************************************/
// Global Variables
/********************************************************************/
long blockingVariable = 500000L;

/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  //Any main local variables must be declared here
  long i = 0L;
  // main entry point
  _DISABLE_COP();
  //EnableInterrupts;
  
/********************************************************************/
  // one-time initializations
/********************************************************************/
  PT1AD1 &= 0x1F;
  DDR1AD1 = 0xE0;
  
/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    ToggleRed();
    Trap1();
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
void ToggleRed(void) {
  PT1AD1 ^= RED_LED;
}

void Trap(long value) {
  long i = 0;
  for (i; i<value; i++) {}
}

void Trap1() {
  long i = 0;
  for (i; i<500000; i++) {}
}
/********************************************************************/
// Interrupt Service Routines
/***********************************/