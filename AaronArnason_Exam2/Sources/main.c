/********************************************************************/
// HC12 Program:  Lab Exam 2 - SCI/RTI/PLL
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       This program uses interrupts to generate a 1 second delay
// Date:          April 3, 2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include <stdlib.h>
#include <stdio.h>

#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"     /* For LED/Switch Functions */
#include "pll_clock.h"  /* Set bus speed to 20Mhz */
#include "rti.h"
#include "sci.h"
#include "misc.h"

//Other system includes or your includes go here
#include <stdlib.h>

/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned long baudRate = 38400;
unsigned long bps;

//int bufferSize = 100;
//char buffer[100];

int i = 0;
unsigned int column = 0;
int count = 0;
char myChar = '.';
unsigned int data;

int color = 0;

char colorChar = ' ';

char numStrings[100];
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
  // Init the Switches/LEDs
  SWL_Init();
  //EnableInterrupts;
	RTI_Init();
  // Init the SCI Module
  bps = sci0_InitMath(Clock_GetBusSpeed(), baudRate);

  // PLL
  // PLLCLOCK == 2 * 16MHZ * synr+1/refdv+1
  // BusSpeed (pass into sci module) == PLLClock / 2
  // given bus speed => multiply by 2, divide by 32 MHz gets a ratio. from that get synr and refdv (32 max value for synr and refdv)

  //RTI
  //RTICTL = 0b10010111; bit 7 => 1 (decimal)/ 0 (binary)
  //                     bit 6-4 => 16MHz / (number in column header)
  //                     bit 3-0 => (16MHz / (number in column header)) / row column

  // SCI module
  // SCI0BD = number --> BusSpeed/(16 * baudRate)

/********************************************************************/
  // one-time initializations
/********************************************************************/
  //buffer[99] = '\0';
/********************************************************************/
  // main program loop
/********************************************************************/
  for (;;) {

    if (SWL_Pushed(SWL_UP) == 1) {
      myChar = '!';
    } else if (SWL_Pushed(SWL_DOWN) == 1) {
      myChar = '?';
    } else if (SWL_Pushed(SWL_CTR) == 1) {
      myChar = '.';
    }

    RTI_Delay(10);
    SWL_TOG(SWL_RED);
    //sci0_txByte('A');
    if (i % 10 == 0) {
      sci0_txByte(myChar);
      SWL_TOG(SWL_GREEN);
      i=0;
    } 
    i++;

    // Part b
    //80 columns
  
    if (sci0_read1(&colorChar) == 1) {
      if (colorChar == 'r' || colorChar == 'R') {
        color = 1;
      } else if (colorChar == 'g' || colorChar == 'G') {
        color = 2;
      } else if (colorChar == 'b' || colorChar == 'B') {
        color = 3;
      }
    }

    if (color == 0) {
      sci0_txStr("\x1b[37m");   //  white
    } else if (color == 1) {
      sci0_txStr("\x1b[31m");   // red
    } else if (color == 2) {
      sci0_txStr("\x1b[32m");   // green
    } else if (color == 3) {
      sci0_txStr("\x1b[34m");    // blue
    }

    sci0_GoToXY(0,0);
    sprintf(numStrings, "%05u", column);
    sci0_txStr(numStrings);

    sci0_txStr("\x1b[37m");   //  white

    sci0_GoToXY(3,column%80);
    data = GetRandom(65, 90);

    sci0_txByte((unsigned char)myChar);
    column++;
  }

}

/********************************************************************/
// Functions
/********************************************************************/


/********************************************************************/
// Interrupt Service Routines
/********************************************************************/

/**sci0_txStrXY(4, 4, buffer);

    for (i = 0; i < bufferSize; i++) {
      buffer[i] = sci0_bread();
      //sci0_txByte(buffer[i]);
      if (buffer[i] == 0xD) { //enter key
        sci0_txStr("\r\n");
        break;
      } 
    }
    buffer[i] = '\0';*/