// SCI library
// Last Modified : February 13 2023
// Revision History:
// May 13th 2014 - Initial Port to C - Simon Walker
// June 8th 2015 - Genric BAUD init added, others removed except for IRDA
// May 23rd 2019 - cleanup, real use of derivative file definitions
// Mar 15th 2022 - cleanup, added interrupt (RDRF only) to init
//               - added ISR template to header

/*
Feb 13th, 2023   - Edited by Carlos for CMPE1250
                 - Added init with no bus speed as parameter
                 - Added advanced typedefs and functions (optional)  

Nov 1st, 2023 - Removed sci0_sxStr function prototype              
*/

/* ADVANCED***************************************************************
If we create a pointer to a structure of this type and make it point to the 
proper SCI Base address, we can use the advanced funtions that would work 
with any sci
*/
typedef struct SCI_Typedef__
{
    //SCIBD OFFSET: 0x0
    unsigned int BD;
    //SCICR1 OFFSET: 0x2
    unsigned char CR1;
    //SCICR2 OFFSET: 0x3  
    unsigned char CR2;
    //SCISR1 OFFSET: 0x4
    unsigned char SR1;
    //SCISR2 OFFSET: 0x5    
    unsigned char SR2;
    //SCIDRH OFFSET: 0x6 
    unsigned char DRH;
    //SCIDRL OFFSET: 0x7    
    unsigned char DRL;
}SCI_Typedef;

typedef SCI_Typedef* SCI_Base;

#define SCI0_BASE (SCI_Base)&SCI0BD//0x000000C8
#define SCI1_BASE (SCI_Base)&SCI1BD//0x000000D0
#define SCI2_BASE (SCI_Base)&SCI2BD//0x000000BE
#define SCI3_BASE (SCI_Base)&SCI3BD//0x000000C0
#define SCI4_BASE (SCI_Base)&SCI4BD//0x00000130
#define SCI5_BASE (SCI_Base)&SCI5BD//0x00000138

/* ADVANCED END************************************************************/


/* BASIC FUNCTIONS, to be coded in CMPE1250*******************************/
//SCI0 - Normal mode: RDX0-> PS0 (PIN 89), TDX0-> PS1 (PIN 90)
typedef enum eBaudRate 
{
    // round(bus_speed / (16 * baudrate))
    BAUD_300_BUS8MHZ = 1667,   // 1666.66666666
    BAUD_1200_BUS8MHZ = 417,   // 416.666666666
    BAUD_9600_BUS8MHZ = 52,    // 52.0833333333
    BAUD_19200_BUS8MHZ = 26,   // 26.0416666666
    BAUD_38400_BUS8MHZ = 13,   // 13.0208333333
    BAUD_57600_BUS8MHZ = 9,    // 8.68055555555

    // No PLL Used
    BAUD_300_BUS16MHZ = 1667,   // 1666.66666666
    BAUD_1200_BUS16MHZ = 417,   // 416.666666666
    BAUD_9600_BUS16MHZ = 52,    // 52.0833333333
    BAUD_19200_BUS16MHZ = 26,   // 26.0416666666
    BAUD_38400_BUS16MHZ = 13,   // 13.0208333333
    BAUD_57600_BUS16MHZ = 9,    // 8.68055555555

    BAUD_300_BUS20MHZ = 4167,   // 4166.66666666 Overflow but works
    BAUD_1200_BUS20MHZ = 1042,  // 1041.66666666
    BAUD_9600_BUS20MHZ = 130,   // 130.208333333
    BAUD_19200_BUS20MHZ = 65,   // 65.1041666666
    BAUD_38400_BUS20MHZ = 33,   // 32.5520833333
    BAUD_57600_BUS20MHZ = 22,   // 21.7013888888
    BAUD_115200_BUS20MHZ = 11,  // 10.8506944444

    BAUD_300_BUS24MHZ = 5000,   // 5000.00000000 Overflow but works
    BAUD_1200_BUS24MHZ = 1250,  // 1250.00000000
    BAUD_9600_BUS24MHZ = 156,   // 156.250000000
    BAUD_19200_BUS24MHZ = 78,   // 78.1250000000
    BAUD_38400_BUS24MHZ = 39,   // 39.0625000000
    BAUD_57600_BUS24MHZ = 26,   // 26.0416666666
    BAUD_115200_BUS24MHZ = 13,  // 13.0208333333

    //BAUD_300_BUS40MHZ = 8333,   // 8333. Not Possible (8333 > 12 bits) does not work
    BAUD_1200_BUS40MHZ = 2083,  // 2083.33333333
    BAUD_9600_BUS40MHZ = 260,   // 260.416666666
    BAUD_19200_BUS40MHZ = 130,  // 130.208333333
    BAUD_38400_BUS40MHZ = 65,   // 65.1041666666
    BAUD_57600_BUS40MHZ = 43,   // 43.4027777777
    BAUD_115200_BUS40MHZ = 22,  // 21.7013888888
    BAUD_230400_BUS40MHZ = 11  // 10.8506944444

} BaudRate;

// default 9600 baud rate. Hard coded.
void sci0_Init(void);

// set baud rate using Enum
void sci0_InitEnum(BaudRate br);

// Programmatic Route
unsigned long sci0_InitMath (unsigned long ulBusClock, unsigned long ulBaudRate);

// Receive a byte from SCI
int sci0_read (unsigned char * pData);

// send a byte over SCI
void sci0_txByte (unsigned char data);


// blocking byte read
// waits for a byte to arrive and returns it
unsigned char sci0_bread(void);

// read a byte, non-blocking
// returns 1 if byte read, 0 if not
unsigned char sci0_rxByte(unsigned char * pData);

// send a null-terminated string over SCI
void sci0_txStr (char const * straddr);

/* BASIC FUNCTIONS END*******************************************************/



/* Other SCIs "Available". These items are optional, for other SCI ports
SCI1 - IRDA mode for using IR module - RDX1-> PS2 (PIN 91), TDX1-> PS3 (PIN 92)
SCI2 - Shared with port J interrupts - RDX2-> PJ0 (PIN 22), TDX2-> PJ1 (PIN 21)

SCI3 - Shared with Mosfets Q7 and Q6 - RDX3-> PM6 (PIN 88), TDX3-> PM7 (PIN 87)
SCI4 - Shared with SPI2 and LCD -      RDX4-> PH4 (PIN 35), TDX4-> PH5 (PIN 34)
SCI5 - Shared with SPI2 and LCD -      RDX5-> PH6 (PIN 33), TDX5-> PH7 (PIN 32)
*/

//ADVANCED FUNCTIONS  - To Work with any sci*************************************
int sci_Init(SCI_Base sci, unsigned long ulBaudRate, int iRDRF_Interrupt);
unsigned char sci0_rxByte(unsigned char * pData);
void sci_txByte (SCI_Base sci, unsigned char data);
void sci_txStr (SCI_Base sci, char const *straddr);
unsigned char sci_rxByte(SCI_Base sci, unsigned char * pData);
/* ADVANCED FUNCTIONS END*******************************************************/
