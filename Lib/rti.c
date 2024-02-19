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