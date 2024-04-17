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
#define lcd_MicroDely { int __x = 10000; while (--__x); }
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
int i;
int delay = 2;
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

  // switch init
  SWL_Init();

  RTI_Init();

  //lcd Init
  lcd_Init();
/********************************************************************/
  // one-time initializations
/********************************************************************/
  i = 0;
/********************************************************************/
  // main program loop
/********************************************************************/

  lcd_Ins(0b00000001);    // clear display set cursor to 0 pos

  // lcd_Data('A');

  // lcd_Data('N');

  // lcd_Data('T');

  // lcd_Data('H');

  // lcd_Data('O');
  
  // lcd_Data('N');
  
  
  // lcd_Data('Y');
  

  // lcd_Data(' ');

  lcd_String("Embedded Is Fun, Hi Bryce, What's up man?! This is cool!");
  
  for (;;)
  {
    
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
