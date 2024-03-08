#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "rti.h"

void RTI_Init(void)
{
    /* 
        bit 7 -> Decimal (not binary)
        bit 6-4 -> Prescale rate: 001 -> (2000): 16Mhz / 2000 = 8Khz
        bit 3-0 -> Modulus counter setting: 0111 (/8): 8Khz / 8 = 1Khz
    */
    RTICTL = 0b10010111;            

    /*
        Enable RTIE module. Set RTIE (bit 7) to 1.
    */
    CRGINT |= CRGINT_RTIE_MASK;
}

// Non Blocking
void RTI_Delay_ms(unsigned int ms) 
{
    /*
        Each rtiMasterCount increment = 1ms
        When rtiMasterCount > variable ms
            -> exit while loop
            -> rtiMasterCount = 0
    */
    while(rtiMasterCount < ms){}
    rtiMasterCount = 0;
}

// Blocking delay for intervalms = n x 1ms
void RTI_Delay(unsigned long Intervalms) {

    // Turn off the RTI
    CRGINT &= ~CRGINT_RTIE_MASK;

    // if RTI Period over, clear flag
    if (CRGFLG_RTIF) {
        CRGFLG = CRGFLG_RTIF_MASK;
    }

    // Start the RTI with 1 ms (configured in RTI init)
    CRGINT |= CRGINT_RTIE_MASK;

    // loop
    while (Intervalms > 0) {
        if (CRGFLG_RTIF) {
            CRGFLG = CRGFLG_RTIF_MASK; 
            Intervalms--;
        }
    }

    // Turn off the RTI
    CRGINT &= ~CRGINT_RTIE_MASK;
}
