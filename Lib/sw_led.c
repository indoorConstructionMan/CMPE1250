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