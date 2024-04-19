/********************************************************************/
// HC12 Program:  Lab 3 : Number Entry / Hex Converter
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       A more detailed explanation of the program is entered here               
// Date:          April 14, 2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "pll_clock.h"
#include "lcd.h"
#include "rti.h"
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
int swUpOld, swDownOld, swLeftOld, swRightOld;
int swUpCurr, swDownCurr, swLeftCurr, swRightCurr;
int swCtrCurr, swCtrOld;
int cursor;
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
  
  // PLL Clock set to 20MHz
  Clock_Set20MHZ();

  SWL_Init();

  //lcd Init
  lcd_Init();
/********************************************************************/
  // one-time initializations
/********************************************************************/
  swUpOld = 0;
  swDownOld = 0;
  swLeftOld = 0;
  swRightOld = 0;
  swUpCurr = 0;
  swDownCurr = 0;
  swLeftCurr = 0;
  swRightCurr = 0;
  swCtrCurr = 0;
  swCtrOld = 0;
  cursor = 0;
/********************************************************************/
  // main program loop
/********************************************************************/
  lcd_Data('Q');
  lcd_AddrXY(1, 3);
  lcd_String("Hello");
  lcd_StringXY(0, 2, "This is spam!");
  lcd_AddrXY(10, 1);
  lcd_DispControl(0, 1);
  lcd_Clear();
  
  for (;;)
  {
    swLeftCurr = SWL_Pushed(SWL_LEFT);
    swRightCurr = SWL_Pushed(SWL_RIGHT);
    swUpCurr = SWL_Pushed(SWL_UP);
    swDownCurr = SWL_Pushed(SWL_DOWN);
    swCtrCurr = SWL_Pushed(SWL_CTR);

    if ((swRightCurr != swRightOld) && swRightCurr) {
      lcd_ShiftR();
    } else if ((swLeftCurr != swLeftOld) && swLeftCurr) {
      lcd_ShiftL();
    } else if ((swUpCurr != swUpOld) && swUpCurr) {
      //lcd_ShiftU();
    } else if ((swDownCurr != swDownOld) && swDownCurr) {
      lcd_String("     ");
    } else if ((swCtrCurr != swCtrOld) && swCtrCurr) {
      lcd_String("Hello");
    }       

    swLeftOld = swLeftCurr;
    swRightOld = swRightCurr;
    swUpOld = swUpCurr;
    swDownOld = swDownCurr;
    swCtrOld = swCtrCurr;

    lcd_DispControl(1, 0);
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
