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
#include "pll_clock.h"
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
long blockingVariableOn = 8507L;
long blockingVariableOff = 8507L;

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
// /********************************************************************/
//   // Part 1
//   for (;;) {
//     OnOffDutyCycle(SWL_RED, blockingVariableOn, blockingVariableOff);
//   }    

  //Clock_Set20MHZ(); // sets clock to 20 mhz
  //Clock_EnableOutput(ClockOutDiv4); // div1 = 20MHz, div2 = 10MHz, div3 = 6.67 MHz, div4 = 5Mhz

  Clock_Set24MHZ(); // sets clock to 24 mhz
  Clock_EnableOutput(ClockOutDiv2); // div1 = 24MHz, div2 = 12MHz, div3 = 8 MHz, div4 = 6 Mhz
  // Part 2
  for (;;) {
    OnOffDutyCycle(SWL_RED, blockingVariableOn, blockingVariableOff);
  }        
}

/********************************************************************/
// Functions
/********************************************************************/
// Calculate the cost per iteration
// How long does it take for OnOffDutyCycle to run
// I have a blocking delay of 100ms -> blocking method is called 2 times
// per iteration -> 50 ms to run

// It is possible to run, but have you seen the clock signal at 8MHz vs 40MHz. 
// 8MHz looks like a (rounded)square wave, and 40Mhz looks like a saw tooth wave.
// As the frequency increases, the integrity of the wave becomes compromised. If 
// this happens, it might cause the output to be unstable. ClockFreq * (synr+1/refdv+1)
