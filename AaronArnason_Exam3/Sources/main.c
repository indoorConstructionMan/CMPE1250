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
#include <stdlib.h>
#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/
//#define questiona
#define questionc
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
int i;
unsigned int minutes;
unsigned int seconds;
unsigned int tenthSeconds;

char clock1[80];


char userBuffer[500];
char myChar;
int charactersRX;
int alphaCount;
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
  sci0_InitMath(Clock_GetBusSpeed(), 19200);

  //segs init
  Segs_Init();

  // lcd init
  lcd_Init();



/********************************************************************/
  // one-time initializations
/********************************************************************/
  i = 0;

  #ifdef questiona
  minutes = 0;
  seconds = 0;
  tenthSeconds = 0;
/********************************************************************/
  // main program loop
/********************************************************************/
  Segs_Init();
  Segs_Clear();


  sci0_ClearScreen();
  sci0_GoToXY(0,0);
  sci0_txStr("Arnason");

  for (;;)
  {
    RTI_Delay(100);
    tenthSeconds++;
    if (tenthSeconds == 10) {
      tenthSeconds = 0;
      seconds++;
    }

    if (seconds == 60) {
      seconds = 0;
      minutes++;
    }

    sprintf(clock1, "%02u:%02u:%0u", minutes, seconds, tenthSeconds);

    sci0_txStrXY(12, 40, clock1);

    Segs_16D(i, Segs_LineTop);

    i++;
    if (i == 9999) i = 0;
  }               
  #endif


  #ifdef questionc
  Segs_Clear();
  charactersRX = 0;
  lcd_DispControl(0,0);
  alphaCount = 0;
  for (;;) {

    myChar = sci0_bread();
    sci0_txByte(myChar);
    charactersRX++;
    Segs_16D(charactersRX, Segs_LineTop);
    
    Segs_8H(6, myChar);
    if (myChar >= 65 && myChar <= 90 || myChar >= 97 && myChar <= 122) {
      alphaCount++;
      lcd_StringXY(0, 0,&myChar);
      sprintf(userBuffer, "Alphas: %04u", alphaCount);
      lcd_StringXY(0, 2, userBuffer);
    }
      
  }
  
  #endif    
}

/********************************************************************/
// Functions
/********************************************************************/
/**

    RTI_Delay(1000);
    SWL_TOG(SWL_RED);

    sci0_txStrXY(5, 5, "Hello World this works");
    Segs_16H(i, Segs_LineTop);
    i++;
    lcd_Data(i);
    //lcd_String("Does this thing even work?");
*/
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
