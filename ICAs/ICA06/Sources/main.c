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

void Clock_Set80MHZ(void);

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

  Clock_Set40MHZ();
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
// I have a blocking delay of 100ms -> blocking method is called 2 times per iteration -> 50 ms to run

// It is possible to run, but have you seen the clock signal at 8MHz vs 40MHz. 8MHz looks like a (rounded)square wave, and 40Mhz looks like a saw tooth wave.
// As the frequency increases, the integrity of the wave becomes compromised. If this happens, it might cause the output to be unstable. ClockFreq * (synr+1/refdv+1)
void Clock_Set80MHZ(void)
{
    // PLLCLK = 2 x OSCCLK x ([SYNR + 1] / [REFDV + 1])
    // PLLCLK = 2 x 16Mhz x ([4 + 1] / [3 + 1])
    // 5/4 (1.25) * 16Mhz * 2 = 40MHz
    // bus is PLLCLOCK / 2, 40MHz / 2 = 20MHz 2.3.2.1 + 2.3.2.2
    SYNR = 5;
    REFDV = 1;
    // we could go faster, but we want to remain stable!
    CLKSEL_PSTP = 1; // 2.3.2.6 (pseudo stop, oscillator runs in stop)
    PLLCTL = 0b11111111; // 2.3.2.7
    // monitor enable (clock is self-monitored)
    // PLL turned on
    // automatic acquisition/tracking mode
    // fast wakeup from full stop
    // can't switch to PLLCLK if (lock=0 and auto=1) - must wait for lock
    while (!CRGFLG_LOCK); 
    // could, but shouldn't block for long
    // now that we are locked, use PLLCLK/2 for bus (20MHz)
    CLKSEL_PLLSEL = 1; // 2.3.2.6
}