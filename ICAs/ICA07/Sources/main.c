/********************************************************************/
// HC12 Program:  ICA07 - Interrupt driven delay and button press
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       This program uses interrupts to generate a 1 second delay
// Date:          February 18, 2024
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
#define PJ0_BUTTON 0b00000010
#define PJ1_BUTTON 0b00000001

#define CLR_PIFJ_FLAG 0b00000011
#define SET_INTERRUPT_PJ1_PJ0 0b00000011
#define SET_RISING_EDGE_PJ1_PJ0 0b00000011
#define SET_INPUT_PJ1_PJ0 0b11111100

//#define PART1
//#define PART2
//#define PART3
#define BONUS
/********************************************************************/
// Local Prototypes
/********************************************************************/
// RTI interrupt prototype
interrupt VectorNumber_Vrti void Vrti_ISR(void);

#ifdef BONUS
  // Input driven Interrupt prototype
  interrupt VectorNumber_Vportj void Vportj_ISR(void);

  // Initialize some registers
  void INPUT_Driven_Init(void);
#endif
/********************************************************************/
// Global Variables
/********************************************************************/
volatile unsigned long rtiMasterCount = 0;

// These are added for input driven ISR, also used in part 2/3
volatile SWL_LEDColour ledToggle;
volatile SWL_LEDColour ledOff;
volatile SWL_LEDColour yellow = SWL_YELLOW;
volatile SWL_LEDColour green = SWL_GREEN;

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
  // Input Driven interrupt
  #ifdef BONUS
    INPUT_Driven_Init();
  #endif
  // RTI init method
  RTI_Init();
  // Init the Switches/LEDs
  SWL_Init();
  //EnableInterrupts;
	EnableInterrupts;

/********************************************************************/
  // one-time initializations
/********************************************************************/
  ledToggle = SWL_RED;
  ledOff = SWL_RED;
/********************************************************************/
  // main program loop
/********************************************************************/
  #ifdef PART1
    // Part 1: just the Interrupt @ 1khz
    for (;;) 
    {

    }
  #endif

  #ifdef PART2
    // Part 2: implement a 100 ms delay.
    for (;;)
    { 
      RTI_Delay_ms(100);
      SWL_TOG(SWL_GREEN);
    }                 
  #endif

  #ifdef PART3
    //Part 3: delay = 1s, 
    for (;;)
    { 
      if(SWL_Pushed(SWL_LEFT) > 0)
      {
        ledToggle = yellow;
        ledOff = green;      
      } else if (SWL_Pushed(SWL_RIGHT) > 0)
      {
        ledToggle = green;
        ledOff = yellow;
      }
      SWL_OFF(ledOff);
      RTI_Delay_ms(1000);
      SWL_TOG(ledToggle);
    }        
  #endif         

  #ifdef BONUS
    // Bonus
    for (;;)
    {
      SWL_OFF(ledOff);
      RTI_Delay_ms(1000);
      SWL_TOG(ledToggle);
    }
  #endif
}

/********************************************************************/
// Functions
/********************************************************************/
#ifdef BONUS
  void INPUT_Driven_Init(void) 
  {
    // set portj0/portj1 as inputs
    DDRJ &= SET_INPUT_PJ1_PJ0;
    // set for rising edge (button pushed?)
    PPSJ |= SET_RISING_EDGE_PJ1_PJ0;
    //Interrupt enable
    PIEJ |= SET_INTERRUPT_PJ1_PJ0;
  }
#endif
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
interrupt VectorNumber_Vrti void Vrti_ISR(void)
{
  CRGFLG = CRGFLG_RTIF_MASK; //clear flag;
  //Perform some action here
  PT1AD1 ^= SWL_RED;
  rtiMasterCount++;
}

#ifdef BONUS
  // Input driven Interrupt service routine
  // Probably should keep this method as short as possible
  interrupt VectorNumber_Vportj void Vportj_ISR(void)
  {
    // This clears the flag
    PIFJ = CLR_PIFJ_FLAG;

    // if PJ1 switch is pressed do this
    if (!(PTJ & PJ1_BUTTON)) {
      ledToggle = yellow;
      ledOff = green;   
    }   

    // if PJ0 switch is pressed do this
    if (!(PTJ & PJ0_BUTTON))
    {
      ledToggle = green;
      ledOff = yellow;   
    }
  }
#endif