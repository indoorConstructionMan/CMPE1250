/********************************************************************/
// HC12 Program:  ICA09 - SCI library Continued
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       This program uses interrupts to generate a 1 second delay
// Date:          March 17, 2024
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
//#define PART1
//#define PART2
#define PART3
/********************************************************************/
// Local Prototypes
/********************************************************************/
void stringFromInt(int summation, char* mySumStr);



/********************************************************************/
// Global Variables
/********************************************************************/
unsigned long baudRate = 19200;
unsigned long bps;
int i = 0;
int index;

unsigned char UpperCaseVowels[5] = {'A', 'E', 'I', 'O', 'U'};
unsigned char LowerCaseVowels[5] = {'a', 'e', 'i', 'o', 'u'};
char rndVwls[21];
char* rndVwlsPtr = rndVwls;

char sumStr[5];
char *mySumStr = sumStr;

unsigned long sum;

unsigned int UpperCaseVowelsIntValues[5] = {65, 69, 73, 79, 85};
unsigned int LowerCaseVowelsIntValues[5] = {97, 101, 105, 111, 117};
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

/********************************************************************/
  // one-time initializations
/********************************************************************/

/********************************************************************/
  // main program loop
/********************************************************************/
#ifdef PART1
  for (;;) {
    RTI_Delay(250);
    for (i = 0; i < 20; i++) {
      if (SWL_Pushed(SWL_CTR) == 1) {
        *rndVwlsPtr = UpperCaseVowels[GetRandom(0,5)];
      } else {
        *rndVwlsPtr = LowerCaseVowels[GetRandom(0,5)];
      }
      rndVwlsPtr++;
    }
    *rndVwlsPtr = '\0';
    rndVwlsPtr -= i;
    SWL_ON(SWL_RED);
    sci0_txStr(rndVwlsPtr);
    //sci0_txStr("\r\n");
    SWL_OFF(SWL_RED);
  }
#endif

#ifdef PART2
  for (;;) {
    RTI_Delay(250);
    sum = 0;
    for (i = 0; i < 20; i++) {
      if (SWL_Pushed(SWL_CTR) == 1) {
        index = GetRandom(0,5);
        *rndVwlsPtr = UpperCaseVowels[index];
        sum += UpperCaseVowelsIntValues[index];
      } else {
        index = GetRandom(0,5);
        *rndVwlsPtr = LowerCaseVowels[index];
        sum += LowerCaseVowelsIntValues[index];
      }
      rndVwlsPtr++;
    }
    *rndVwlsPtr = '\0';
    rndVwlsPtr -= i;

    stringFromInt(sum, mySumStr);

    SWL_ON(SWL_RED);
    sci0_txStr(rndVwlsPtr);
    sci0_txStr("\x1b[1C");
    sci0_txStr(mySumStr);
    sci0_txStr("\x1b[1C");
    SWL_OFF(SWL_RED);
  }
#endif
  sci0_txStr("\x1b[0;0H");
  sci0_txStr("\x1b[38;2;255;0;255m");
  sci0_txStr("Aaron Arnason");
  sci0_txStr("\x1b[37m");
  sci0_txStr("\r\n");

#ifdef PART3
  for (;;) {
    RTI_Delay(250);
    sum = 0;
    for (i = 0; i < 20; i++) {
      if (SWL_Pushed(SWL_CTR) == 1) {
        index = GetRandom(0,5);
        *rndVwlsPtr = UpperCaseVowels[index];
        sum += UpperCaseVowelsIntValues[index];
      } else {
        index = GetRandom(0,5);
        *rndVwlsPtr = LowerCaseVowels[index];
        sum += LowerCaseVowelsIntValues[index];
      }
      rndVwlsPtr++;
    }
    *rndVwlsPtr = '\0';
    rndVwlsPtr -= i;

    stringFromInt(sum, mySumStr);

    SWL_ON(SWL_RED);
    sci0_txStr("\x1b[0;0H"); // 0,0
    sci0_txStr("\x1b[1B");   // next row
    sci0_txStr("\x1b[1B");   // next row == 3rd row
    sci0_txStr("\x1b[32m");  // green text
    sci0_txStr("\x1b[0K");   // erase existing text in this row
    sci0_txStr(rndVwlsPtr);
    sci0_txStr("\x1b[1C");   // 1 space to right
    sci0_txStr("\x1b[38;2;255;255;0m");  // yellow text
    sci0_txStr(mySumStr);
    sci0_txStr("\x1b[1C");   // 1 space to right
    sci0_txStr("\x1b[0;0H");
    sci0_txStr("\x1b[1B"); 
    sci0_txStr("\x1b[1B"); 
    sci0_txStr("\x1b[1B"); 
    sci0_txStr("\x1b[1B"); 
    sci0_txStr("\x1b[37m");  // default color white
    sci0_txStr("Count");  
    
    SWL_OFF(SWL_RED);
  }
#endif


}

/********************************************************************/
// Functions
/********************************************************************/
// Really Ugly function....
void stringFromInt(int summation, char* mySumStr) {  
  int remainder1, remainder2, remainder3, remainder4;
  remainder1 = summation % 10;
  summation /= 10;
  remainder2 = summation % 10;
  summation /= 10;
  remainder3 = summation % 10;
  summation /= 10;
  remainder4 = summation % 10;

  *mySumStr = 48 + remainder4;
  mySumStr++;

  *mySumStr = 48 + remainder3;
  mySumStr++;

  *mySumStr = 48 + remainder2;
  mySumStr++;

  *mySumStr = 48 + remainder1;
  mySumStr++;

  mySumStr -= 4;
}


/********************************************************************/
// Interrupt Service Routines
/********************************************************************/

