/********************************************************************/
// HC12 Program:  Just fun terminal emulator stuff
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       This program uses interrupts to generate a 1 second delay
// Date:          March 18, 2024
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
#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/
/********************************************************************/
// Local Prototypes
/********************************************************************/
void command(char *cmd);

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned long baudRate = 115200;

unsigned long bps;
int i = 0;
int index;
int txStringsCount = 0;

unsigned char UpperCaseVowels[5] = {'A', 'E', 'I', 'O', 'U'};
unsigned char LowerCaseVowels[5] = {'a', 'e', 'i', 'o', 'u'};
char rndVwls[21];
char* rndVwlsPtr = rndVwls;

char sumStr[5];
char *mySumStr = sumStr;

unsigned long sum;

unsigned int UpperCaseVowelsIntValues[5] = {65, 69, 73, 79, 85};
unsigned int LowerCaseVowelsIntValues[5] = {97, 101, 105, 111, 117};


char count[500];
char greetings[100] = "\x1b[32maaron@cmpe1250mcu:~# \x1b[37m";

/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  unsigned char data = 'A';
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
  for (;;) {
    SWL_ON(SWL_RED);

    sci0_txStr(greetings);

    for (i = 0; i < 500; i++) {
      count[i] = sci0_bread();
      sci0_txByte(count[i]);
      if (count[i] == 0xD) {
        sci0_txStr("\r\n");
        break;
      } 
    }
    count[i] = '\0';
    
    command(count);
    SWL_OFF(SWL_RED);
  }
}

/********************************************************************/
// Functions
/********************************************************************/
void command(char *cmd) {
  char cmd1[7] = "whoami";
  int i = 0;
  for (i = 0; i < 7; i++) {
    if (cmd1[i] == cmd[i]) {

    } else {
      sci0_txStr("bash: ");
      sci0_txStr(cmd);
      sci0_txStr(": command not found");
      sci0_txStr("\r\n");
      return;
    }
  }
  sci0_txStr("root\r\n");
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/

