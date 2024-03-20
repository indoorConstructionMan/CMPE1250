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
//#include <stdlib.h>
#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/
/********************************************************************/
// Local Prototypes
/********************************************************************/
void command(char *cmd);
void badFileOrCommand(char *cmd);
int isCommand(char *cmd, char *cmd1);
void runCommand(int commandIndex);
void userInput(char *buff, int bufferSize);

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned long baudRate = 115200;

unsigned long bps;
int index;
int result = 0;

unsigned long sum;

unsigned int UpperCaseVowelsIntValues[5] = {65, 69, 73, 79, 85};
unsigned int LowerCaseVowelsIntValues[5] = {97, 101, 105, 111, 117};


char *currentColor;
char userBuffer[500];
char greetings[100] = "\x1b[32maaron@\x1b[31mcmpe1250mcu:\x1b[33m~# \x1b[37m"; 


// Register a new function
int commandCount = 22;
char *myCommands[] = {
    "whoami\0",
    "set RED on\0",
    "set RED off\0",
    "set GREEN on\0",
    "set GREEN off\0",  //5
    "set YELLOW on\0",
    "set YELLOW off\0",
    "set LEDS on",
    "set LEDS off",
    "clear\0",  //10
    "set FG red",
    "set FG green",
    "set FG blue",
    "set FG white",
    "set BG white",  //15
    "set BG black",
    "set BG red",
    "set BG green",
    "set BG blue",
    "set BAUD 9600",  // 20
    "set BAUD 115200",
    "lscmds"
  };
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
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
    userInput(userBuffer, 500);
    command(userBuffer);
  }
}

/********************************************************************/
// Functions
/********************************************************************/
void userInput(char *buff, int bufferSize) {
  int i = 0;
  sci0_txStr(greetings);
  sci0_txStr(currentColor);

  for (i = 0; i < bufferSize; i++) {
    buff[i] = sci0_bread();
    sci0_txByte(buff[i]);
    if (buff[i] == 0xD) {
      sci0_txStr("\r\n");
      break;
    } 
  }
  buff[i] = '\0';
}

void command(char *cmd) {
  int index;
  for (index = 0; index < commandCount; index++) {
    if (isCommand(cmd, myCommands[index])) {
      runCommand(index);
      return;
    }  
  }

  badFileOrCommand(cmd);
}

void runCommand(int commandIndex) {
  int j = 0;
  switch(commandIndex) {
    case 0:
      sci0_txStr("root\r\n");
      break;
    case 1:
      SWL_ON(SWL_RED);
      break;
    case 2:
      SWL_OFF(SWL_RED);
      break;
    case 3:
      SWL_ON(SWL_GREEN);
      break;
    case 4:
      SWL_OFF(SWL_GREEN);
      break;
    case 5:
      SWL_ON(SWL_YELLOW);
      break;
    case 6:
      SWL_OFF(SWL_YELLOW);
      break;
    case 7:
      SWL_ON(SWL_ALL);
      break;
    case 8:
      SWL_OFF(SWL_ALL);
      break;
    case 9:
      sci0_txStr("\x1b[2J");
      sci0_txStr("\x1b[0;0H");
      break;
    case 10:
      currentColor = "\x1b[31m";
      break;
    case 11:
      currentColor = "\x1b[32m";
      break;
    case 12:
      currentColor = "\x1b[34m";  
      break;
    case 13:
      currentColor = "\x1b[37m";
      break;
    case 14:
      sci0_txStr("\x1b[47m");
      sci0_txStr("\x1b[2J");
      sci0_txStr("\x1b[0;0H");
      break;
    case 15:
      sci0_txStr("\x1b[40m");
      sci0_txStr("\x1b[2J");
      sci0_txStr("\x1b[0;0H");
      break;  
    case 16:
      sci0_txStr("\x1b[41m");
      sci0_txStr("\x1b[2J");
      sci0_txStr("\x1b[0;0H");
      break;
    case 17:
      sci0_txStr("\x1b[42m");
      sci0_txStr("\x1b[2J");
      sci0_txStr("\x1b[0;0H");
      break;
    case 18:
      sci0_txStr("\x1b[44m");
      sci0_txStr("\x1b[2J");
      sci0_txStr("\x1b[0;0H");
      break;
    case 19:
      sci0_txStr("Setting Baud rate to 9600. In 3s....\r\n");
      RTI_Delay(1000);
      sci0_txStr("2s....");
      RTI_Delay(1000);
      sci0_txStr("1s....");
      RTI_Delay(1000);
      result = sci0_InitMath(Clock_GetBusSpeed(), 9600);
      RTI_Delay(5000);
      break;
    case 20:
      sci0_txStr("Setting Baud rate to 115200. In 3s....\r\n");
      RTI_Delay(1000);
      sci0_txStr("2s....");
      RTI_Delay(1000);
      sci0_txStr("1s....");
      RTI_Delay(1000);
      result = sci0_InitMath(Clock_GetBusSpeed(), 115200);
      RTI_Delay(5000);
      break;
    case 21:
      sci0_txStr("\r\n");
      for (j; j < commandCount; j++) {
        sci0_txStr("Invoke Command ==> '");
        sci0_txStr(myCommands[j]);
        sci0_txStr("'");
        sci0_txStr("\r\n");
      }
      sci0_txStr("\r\n");
      break;
    default:
      break;
  }
}

int isCommand(char *cmd, char *cmd1) {
  int flag = 0;
  int i = 0;
  while(cmd1[i] != '\0') {
    if (cmd1[i] == cmd[i]) {
      flag = 1;
    } else {
      return 0;
    }
    i++;
  }
  return flag;
}


void badFileOrCommand(char *cmd) {
  sci0_txStr("bash: ");
  sci0_txStr(cmd);
  sci0_txStr(": command not found");
  sci0_txStr("\r\n");
}

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/