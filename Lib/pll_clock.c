#include <hidef.h>      
#include "derivative.h" 
#include "pll_clock.h"

void Clock_Set8MHZ(void) 
{

    // PLLCLK = 2 x OSCCLK x ([SYNR + 1] / [REFDV + 1])
    // PLLCLK = 2 x 16Mhz x ([4 + 1] / [3 + 1])
    // 5/4 (1.25) * 16Mhz * 2 = 40MHz
    // bus is PLLCLOCK / 2, 40MHz / 2 = 20MHz 2.3.2.1 + 2.3.2.2
    SYNR = 2;
    REFDV = 5;
    // we could go faster, but we want to remain stable!
    CLKSEL_PSTP = 1; // 2.3.2.6 (pseudo stop, oscillator runs in stop)
    PLLCTL = 0b11111111; // 2.3.2.7
    // monitor enable (clock is self-monitored)
    // PLL turned on
    // automatic acquisition/tracking mode
    // fast wakeup from full stop
    // can't switch to PLLCLK if (lock=0 and auto=1) - must wait for lock
    while (!CRGFLG_LOCK); 
    // could, but shouldn't block for long
    // now that we are locked, use PLLCLK/2 for bus (20MHz)
    CLKSEL_PLLSEL = 1; // 2.3.2.6
}

void Clock_Set20MHZ (void)
{
    // PLLCLK = 2 x OSCCLK x ([SYNR + 1] / [REFDV + 1])
    // PLLCLK = 2 x 16Mhz x ([4 + 1] / [3 + 1])
    // 5/4 (1.25) * 16Mhz * 2 = 40MHz
    // bus is PLLCLOCK / 2, 40MHz / 2 = 20MHz 2.3.2.1 + 2.3.2.2
    SYNR = 4;
    REFDV = 3;
    // we could go faster, but we want to remain stable!
    CLKSEL_PSTP = 1; // 2.3.2.6 (pseudo stop, oscillator runs in stop)
    PLLCTL = 0b11111111; // 2.3.2.7
    // monitor enable (clock is self-monitored)
    // PLL turned on
    // automatic acquisition/tracking mode
    // fast wakeup from full stop
    // can't switch to PLLCLK if (lock=0 and auto=1) - must wait for lock
    while (!CRGFLG_LOCK); 
    // could, but shouldn't block for long
    // now that we are locked, use PLLCLK/2 for bus (20MHz)
    CLKSEL_PLLSEL = 1; // 2.3.2.6
}

void Clock_Set24MHZ(void)
{
    // PLLCLK = 2 x OSCCLK x ([SYNR + 1] / [REFDV + 1])
    // PLLCLK = 2 x 16Mhz x ([4 + 1] / [3 + 1])
    // 5/4 (1.25) * 16Mhz * 2 = 40MHz
    // bus is PLLCLOCK / 2, 40MHz / 2 = 20MHz 2.3.2.1 + 2.3.2.2
    SYNR = 6;
    REFDV = 4;
    // we could go faster, but we want to remain stable!
    CLKSEL_PSTP = 1; // 2.3.2.6 (pseudo stop, oscillator runs in stop)
    PLLCTL = 0b11111111; // 2.3.2.7
    // monitor enable (clock is self-monitored)
    // PLL turned on
    // automatic acquisition/tracking mode
    // fast wakeup from full stop
    // can't switch to PLLCLK if (lock=0 and auto=1) - must wait for lock
    while (!CRGFLG_LOCK); 
    // could, but shouldn't block for long
    // now that we are locked, use PLLCLK/2 for bus (20MHz)
    CLKSEL_PLLSEL = 1; // 2.3.2.6
}

void Clock_Set40MHZ(void)
{
    // PLLCLK = 2 x OSCCLK x ([SYNR + 1] / [REFDV + 1])
    // PLLCLK = 2 x 16Mhz x ([4 + 1] / [3 + 1])
    // 5/4 (1.25) * 16Mhz * 2 = 40MHz
    // bus is PLLCLOCK / 2, 40MHz / 2 = 20MHz 2.3.2.1 + 2.3.2.2
    SYNR = 4;
    REFDV = 1;
    // we could go faster, but we want to remain stable!
    CLKSEL_PSTP = 1; // 2.3.2.6 (pseudo stop, oscillator runs in stop)
    PLLCTL = 0b11111111; // 2.3.2.7
    // monitor enable (clock is self-monitored)
    // PLL turned on
    // automatic acquisition/tracking mode
    // fast wakeup from full stop
    // can't switch to PLLCLK if (lock=0 and auto=1) - must wait for lock
    while (!CRGFLG_LOCK); 
    // could, but shouldn't block for long
    // now that we are locked, use PLLCLK/2 for bus (20MHz)
    CLKSEL_PLLSEL = 1; // 2.3.2.6
}