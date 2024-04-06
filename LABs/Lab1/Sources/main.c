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

char myOperand1[5] = {'0', '0', '0', '0', '\0'};
char myOperand2[5] = {'0', '0', '0', '0', '\0'};

char *operand1;
char *operand2;

unsigned char character;
operation currentOp = AND_OPERATION;

int xPosition = 0, yPosition = 0;
int xOffset = 5, yOffset = 13;
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

    // Draw all dynamic data
    sci0_DrawState(operand1, operand2, currentOp);

    // set cursor to the correct position being edited (so it blinks at correct position)
    sci0_GoToXY(xOffset + yPosition, yOffset + xPosition);

    // Blocking read, waiting for character from user.
    character = sci0_bread();

    // if character is tab, change the operand and start at the beginning
    if (character == '\x09') {
      if (yPosition == 0) {
        xPosition = 0;
        yPosition = 1;
      } else {
        xPosition = 0;
        yPosition = 0;
      } 
    } 
    
    // If character was instead ampersand or Vertical bar, set the appropriate operator (to be passed to drawstate)
    else if (character == '&') {
      currentOp = AND_OPERATION;
    } else if (character == '|') {
      currentOp = OR_OPERATION;
    } 
    
    // else we only want to make changes if the user passes in a valid ascii key (including upper case and lower case abcdef. 0-9)
    // based on that we assign character to operand, and increase the position to the next position
    else {
      for (i = 0; i < 16; i++){
        if (character == myDigits[i]) {
          if (yPosition == 0) {
            operand1[xPosition%4] = character;
            xPosition++;
          } else {
            operand2[xPosition%4] = character;
            xPosition++;
          }
          if (xPosition == 4) {
            xPosition = 0;
            if (yPosition == 0) {
              yPosition = 1;
            } else {
              yPosition = 0;
            }
          }
        }

        // This just handles the characters that are lower case.
        if (i > 9) {
          if (character == (myDigits[i] + 32)) {
            if (yPosition == 0) {
            operand1[xPosition%4] = character;
            xPosition++;
          } else {
            operand2[xPosition%4] = character;
            xPosition++;
          }
          if (xPosition == 4) {
            xPosition = 0;
            if (yPosition == 0) {
              yPosition = 1;
            } else {
              yPosition = 0;
            }
          }

          }
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
