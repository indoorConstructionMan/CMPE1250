/********************************************************************/
// HC12 Program:  Exam 3 : Final Exam
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       A more detailed explanation of the program is entered here               
// Date:          April 26, 2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"
#include "pll_clock.h"
#include "misc.h"
#include "lcd.h"
#include "sci.h"
#include "segs.h"
#include "rti.h"

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
int i;
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
  
  // switch / leds
  SWL_Init();

  // pll clock
  Clock_Set20MHZ();

  // rti init
  RTI_Init();

  // sci init
  sci0_InitMath(Clock_GetBusSpeed(), 115200);

  //segs init
  Segs_Init();

  // lcd init
  lcd_Init();



/********************************************************************/
  // one-time initializations
/********************************************************************/
  i = 0;
/********************************************************************/
  // main program loop
/********************************************************************/
  Segs_Clear();
  lcd_Clear();

  for (;;)
  {
    RTI_Delay(1000);
    SWL_TOG(SWL_RED);

    sci0_txStrXY(5, 5, "Hello World this works");
    Segs_16H(i, Segs_LineTop);
    i++;
    lcd_Data(i);
    //lcd_String("Does this thing even work?");
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
