/********************************************************************/
// HC12 Program:  ICA08 - SCI library
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       This program uses interrupts to generate a 1 second delay
// Date:          March 13, 2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"     /* For LED/Switch Functions */
#include "pll_clock.h"  /* Set bus speed to 20Mhz */
#include "rti.h"
#include "sci.h"
#include "misc.h"

//Other system includes or your includes go here
//#include <stdlib.h>
//#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
// RTI interrupt prototype
//interrupt VectorNumber_Vrti void Vrti_ISR(void);
int isVowel(unsigned char pData);
/********************************************************************/
// Global Variables
/********************************************************************/
unsigned char vowels[10] = {'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u'};

/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  //Any main local variables must be declared here
  unsigned char data = 'A';
  // main entry point
  _DISABLE_COP();
  // Set Bus Speed
  Clock_Set20MHZ();
  // Init the Switches/LEDs
  SWL_Init();
  //EnableInterrupts;
	RTI_Init();
  // Init the SCI Module
  sci0_Init();

/********************************************************************/
  // one-time initializations
/********************************************************************/

/********************************************************************/
  // main program loop
/********************************************************************/
  for (;;) {
    RTI_Delay(50);
    SWL_TOG(SWL_RED);
    data = GetRandom(65, 90);
    sci0_txByte(data);
    if (sci0_read(&data)) {
      if(isVowel(data)) {
        SWL_OFF(SWL_YELLOW);
        SWL_ON(SWL_GREEN);
      } else {
        SWL_OFF(SWL_GREEN);
        SWL_ON(SWL_YELLOW);
      }
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/
int isVowel(unsigned char pData) {
  // a, e, i, o, u
  int i;
  for (i = 0; i < 10; i++){
    if (vowels[i] == pData) return 1;
  }
  return 0;
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/

