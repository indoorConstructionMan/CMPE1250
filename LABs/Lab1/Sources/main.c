/********************************************************************/
// HC12 Program:  LAB1 - Calculator
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz
// Author:        Aaron Arnason
// Details:       This program uses interrupts to generate a 1 second delay
// Date:          April 5, 2024
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "pll_clock.h"  /* Set bus speed to 20Mhz */
#include "rti.h"
#include "sci.h"
#include "misc.h"

// Other system includes or your includes go here
// #include <stdlib.h>
#include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
/********************************************************************/
// Global Variables
/********************************************************************/
unsigned long baudRate = 38400;
unsigned long calculatedBaudRate;

char myOperand1[4];
char myOperand2[4];

char *operand1;
char *operand2;

unsigned char character;
operation currentOp = AND_OPERATION;

int xPosition = 0, yPosition = 0;
int xOffset = 13,yOffset = 5;
char myDigits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  int i = 0;
  // Any main local variables must be declared here
  //  main entry point
  _DISABLE_COP();

  // Set Bus Speed
  Clock_Set20MHZ();

  // rti init
  RTI_Init();

  // Init the SCI Module
  calculatedBaudRate = sci0_InitMath(Clock_GetBusSpeed(), baudRate);

  /********************************************************************/
  // one-time initializations
  /********************************************************************/
  operand1 = myOperand1;
  operand2 = myOperand2;
  /********************************************************************/
  // main program loop
  /********************************************************************/

  sci0_ClearScreen();
  sci0_drawStaticData();
  for (;;)
  {
    sci0_GoToXY(8, 11);
    sci0_DrawState("ABCD", "1234", currentOp);
    character = sci0_bread();
    if (character == '\x09') {
      if (currentOp == AND_OPERATION) {
        currentOp = OR_OPERATION;
      } else if (currentOp == OR_OPERATION) {
        currentOp = AND_OPERATION;
      } 
    } else if (character == '&') {
      currentOp = AND_OPERATION;
    } else if (character == '|') {
      currentOp = OR_OPERATION;
    } else {
      for (i = 0; i < 16; i++){
        if (character == myDigits[i]) {
          sci0_txStrXY(xOffset + xPosition, yOffset + yPosition, (char*)&character);
        }
      }
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
