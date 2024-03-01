/********************************************************************/
// HC12 Program:  ICA06 - PLL/BUS Speed
// Processor:     MC9S12XDP512
// Bus Speed:     **Assign BUS Speed 8/16/20/24/40 MHz (80 Doesn't work)
// Author:        Aaron Arnason
// Details:       A more detailed explanation of the program is entered here               
// Date:          February 19, 2024
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
//#define PART1
#define PART2
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
long blockingVariableOn = 17025L;
long blockingVariableOff = 17025L;

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
  #ifdef PART1
    // Part 1
    for (;;) {
      OnOffDutyCycle(SWL_RED, blockingVariableOn, blockingVariableOff);
    }    
  #endif

  #ifdef PART2
    
    if (SWL_Pushed(SWL_LEFT) == 1) {
      Clock_Set8MHZ();
    } else if (SWL_Pushed(SWL_CTR) == 1) {
      Clock_Set20MHZ();
    } else if (SWL_Pushed(SWL_RIGHT) == 1) {
      Clock_Set24MHZ();
    }
    // Part 2
    for (;;) {
      OnOffDutyCycle(SWL_RED, blockingVariableOn, blockingVariableOff);
    }     
  #endif
}

/********************************************************************/
// Functions
/********************************************************************/
// Calculate the cost per iteration
// How long does it take for OnOffDutyCycle to run
// I have a blocking delay of 100ms -> blocking method 

// It is possible to run, but have you seen the clock signal at 8MHz vs 40MHz. 
// 8MHz looks like a (rounded)square wave, and 40Mhz looks like a saw tooth wave.
// As the frequency increases, the integrity of the wave becomes compromised. If 
// this happens, it might cause the output to be unstable. ClockFreq * (synr+1/refdv+1)

// bus_speed = 2 * PLLCLK
// PLLCLK/2*OSCCLK = (SYNR + 1)/(REFDV + 1)
// bus_speed = 24 -> pllCLk = 48
// 48/32 = (SYNR+1)/(REFDV+1) = 3/2