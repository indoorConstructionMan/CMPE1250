#include <hidef.h>     
#include "derivative.h"
#include "sw_led.h"

void SWL_Init(void) {
    PT1AD1 = 0b00000000;
    DDR1AD1 = 0b11100000;
    ATD1DIEN1 = 0b00011111;
}

void SWL_ON(SWL_LEDColour led) {
    PT1AD1 |= led;
}

void SWL_OFF (SWL_LEDColour led) {
    PT1AD1 &= ~led;
}

void SWL_TOG (SWL_LEDColour led) {
    PT1AD1 ^= led;
}

int SWL_Pushed (SWL_SwitchPos pos) {
    int pushed = 0;
    if (PT1AD1 & pos) {
        pushed = 1;
    }
    return pushed;
}

int SWL_Any (void) {
    int anyPushed = 0;
    if (PT1AD1 & SWL_ANY) {
        anyPushed = 1;
    }
    return anyPushed;
}

int GetLedCount(void) {
  int ledCount = 0;
  if (PT1AD1 & SWL_RED) {
    ledCount++;
  }

  if (PT1AD1 & SWL_GREEN) {
    ledCount++;
  }

  if (PT1AD1 & SWL_YELLOW) {
    ledCount++;
  }
  return ledCount;
}
/* 
  Function  - void OnOffDutyCycle(SWL_LEDColour led, long dutyOnCount, long dutyOffCount)
  Arguments - SWL_LEDColor led: The LED that you want to PWM.
            - long dutyOnCount: The count for the ON part of the cycle
            - long dutyOffCount: The count for the OFF part of the cycle
  Purpose: To create a duty cycle specified by the user once the Period is determined
           Period is related to count, and duty cycle is a percent of that count.
           I had a count of 3404 for 50hz, and to turn the LED 5ms -> count = 851
           and to turn the LED for 15 ms -> count = 2552
  Return: None
*/
void OnOffDutyCycle(SWL_LEDColour led, long dutyOnCount, long dutyOffCount) {
  long i = 0;

  PT1AD1 |= led;  
  for (i; i<dutyOnCount; i++) {}
  
  PT1AD1 &= ~led;
  i = 0;
  for (i; i<dutyOffCount; i++) {}
}

/*
Function    - int GetSwitchPushedCount(void)
  Arguments - void
  Purpose: To determine the number of buttons that are currently being pressed.
           It grabs the value of PT1AD1 -> myReg
           It then bitwise ands with 1, and if it's true, count++
           Then the myReg variable is bit shifted to the right
           This for loop iterates 5 times for the 5 switches.
  Return: int : The number of switches pushed
*/
int GetSwitchPushedCount(void) {
    int count = 0;
    int myReg = PT1AD1;
    int i = 0;
    
    for (i = 0; i < 5; i++) {
      if (myReg & 0b00000001) {
        count++;
      }
      myReg = myReg >> 1;
    }

    return count;
}
