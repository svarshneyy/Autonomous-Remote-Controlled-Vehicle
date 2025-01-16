//------------------------------------------------------------------------------

//  Description: Contains functions that initialize all ports and pins.

//  Sanchit Varshney
//  Sep 2024
//  Built with Code Composer Version: 12.8

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  <string.h>
#include  "macros.h"

//------------------------------------------------------------------------------

//PxSEL determines GPIO or Function; 00 is GPIO, 01 is Uxxxxx (primary), 10 is unknown (secondary), 11 is ADC (Tertiary)
//PxDIR determines Direction. Can be

//------------------------------------------------------------------------------

//Initializes every port
void Init_Ports(void)
{
    Init_Port1();
    Init_Port2();
    Init_Port3();
    Init_Port4();
    Init_Port5();
    Init_Port6();
}

void Init_Port1(void)
{ // Configure Port 1
    //------------------------------------------------------------------------------

    P1DIR = 0x00; // Set P1 direction to input
    P1OUT = 0x00; // P1 set Low

    P1SEL0 &= ~RED_LED; // Set RED_LED as GP I/O
    P1SEL1 &= ~RED_LED; // Set RED_LED as GP I/O
    P1OUT &= ~RED_LED; // Set Red LED Off
    P1DIR |= RED_LED; // Set Red LED direction to output

    P1SELC |= V_A1_SEEED; // ADC input for A1_SEEED

    P1SELC |= V_DETECT_L; // ADC input for V_DETECT_L

    P1SELC |= V_DETECT_R; // ADC input for V_DETECT_R

    P1SELC |= V_A4_SEEED; // ADC input for V_A4_SEEED

    P1SELC |= V_THUMB; // ADC input for V_THUMB

    P1SEL0 |= UCA0TXD; // UCA0TXD pin
    P1SEL1 &= ~UCA0TXD; // UCA0TXD pin

    P1SEL0 |= UCA0RXD; // UCA0RXD pin
    P1SEL1 &= ~UCA0RXD; // UCA0RXD pin
}

void Init_Port2(void)
{ // Configure Port 2
    //------------------------------------------------------------------------------
    P2OUT = 0x00; // P2 set Low
    P2DIR = 0x00; // Set P2 direction to output

    //P2 Pin 0
    P2SEL0 &= ~SLOW_CLK; // SLOW_CLK GPIO operation
    P2SEL1 &= ~SLOW_CLK; // SLOW_CLK GPIO operation
    P2OUT &= ~SLOW_CLK; // Initial Value = Low / Off
    P2DIR |= SLOW_CLK; // Direction = output

    //P2 Pin 1
    P2SEL0 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
    P2SEL1 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
    P2OUT &= ~CHECK_BAT; // Initial Value = Low / Off
    P2DIR |= CHECK_BAT; // Direction = output

    //P2 Pin 2
    P2SEL0 &= ~IR_LED; // P2_2 GPIO operation
    P2SEL1 &= ~IR_LED; // P2_2 GPIO operation
    P2OUT &= ~IR_LED; // Initial Value = Low / Off
    P2DIR |= IR_LED; // Direction = output

    //P2 Pin 3
    P2SEL0 &= ~SW2; // SW2 Operation
    P2SEL1 &= ~SW2; // SW2 Operation
    P2DIR &= ~SW2; // Direction = input
    P2PUD |= SW2; // Configure pullup resistor
    P2REN |= SW2; // Enable pullup resistor
    P2IES |= SW2; // P2.0 Hi/Lo edge interrupt
    P2IFG &= ~SW2; // P2.3 IFG SW2 cleared
    P2IE |= SW2; // P2.3 SW2 interrupt enabled

    //P2 Pin 4
    P2SEL0 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
    P2SEL1 &= ~IOT_RUN_RED; // IOT_RUN_CPU GPIO operation
    P2OUT &= ~IOT_RUN_RED; // Initial Value = Low / Off
    P2DIR |= IOT_RUN_RED; // Direction = output

    //P2 Pin 5
    P2SEL0 &= ~DAC_ENB; // DAC_ENB GPIO operation
    P2SEL1 &= ~DAC_ENB; // DAC_ENB GPIO operation
    P2OUT |= DAC_ENB; // Initial Value = High
    P2DIR |= DAC_ENB; // Direction = output

    //P2 Pin 6
    P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
    P2SEL1 |= LFXOUT; // LFXOUT Clock operation

    //P2 Pin 7
    P2SEL0 &= ~LFXIN; // LFXIN Clock operation
    P2SEL1 |= LFXIN; // LFXIN Clock operation

    //------------------------------------------------------------------------------
}

void Init_Port3(void)
{ // Configure Port 3
    //------------------------------------------------------------------------------

    //P3 pin 0
    P3SEL0 &= ~TEST_PROBE; // TEST_PROBE GPIO operation
    P3SEL1 &= ~TEST_PROBE; // TEST_PROBE GPIO operation
    P3DIR &= ~TEST_PROBE; // Direction = input

    //P3 pin 1
    P3SEL0 &= ~OA2O; // OA2O GPIO operation
    P3SEL1 &= ~OA2O; // OA2O GPIO operation
    P3DIR &= ~OA2O; // Direction = input

    //P3 pin 2
    P3SEL0 &= ~OA2N; // OA2N GPIO operation
    P3SEL1 &= ~OA2N; // OA2N GPIO operation
    P3DIR &= ~OA2N; // Direction = input

    //P3 pin 3
    P3SEL0 &= ~OA2P; // OA2P GPIO operation
    P3SEL1 &= ~OA2P; // OA2P GPIO operation
    P3DIR &= ~OA2P; // Direction = input

    //P3 pin 4
    P3SEL0 &= ~SMCLK; // SMCLK GPIO operation
    P3SEL1 &= ~SMCLK; // SMCLK GPIO operation
    P3DIR &= ~SMCLK; // Direction = input

    //P3 pin 5
    P3SEL0 &= ~DAC_CNTL; // DAC_CNTL GPIO operation
    P3SEL1 &= ~DAC_CNTL; // DAC_CNTL GPIO operation
    P3DIR &= ~DAC_CNTL; // Direction = input

    //P3 pin 6
    P3SEL0 &= ~IOT_LINK_GRN; // IOT_LINK_GRN GPIO operation
    P3SEL1 &= ~IOT_LINK_GRN; // IOT_LINK_GRN GPIO operation
    P3DIR |= IOT_LINK_GRN; // Direction = output
    P3OUT &= ~IOT_LINK_GRN; //Initial Value = Low/Off

    //P3 pin 7
    P3SEL0 &= ~IOT_EN; // IOT_EN GPIO operation
    P3SEL1 &= ~IOT_EN; // IOT_EN GPIO operation
    P3DIR |= IOT_EN; // Direction = output
    P3OUT &= ~IOT_EN; //Set initial to 0

    //------------------------------------------------------------------------------
}

void Init_Port4(void)
{ // Configure PORT 4
    //------------------------------------------------------------------------------
    P4OUT = 0x00; // P4 set Low
    P4DIR = 0x00; // Set P4 direction to output

    //P4 Pin 0
    P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
    P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
    P4OUT &= ~RESET_LCD; // Initial Value = Low / Off
    P4DIR |= RESET_LCD; // Direction = output

    //P4 Pin 1
    P4SEL0 &= ~SW1; // SW1 set as I/0
    P4SEL1 &= ~SW1; // SW1 set as I/0
    P4DIR &= ~SW1; // SW1 Direction = input
    P4PUD |= SW1; // Configure pull-up resistor SW1
    P4REN |= SW1; // Enable pull-up resistor SW1
    P4IES |= SW1; // SW1 Hi/Lo edge interrupt
    P4IFG &= ~SW1; // IFG SW1 cleared
    P4IE |= SW1; // SW1 interrupt Enabled

    //P4 Pin 2
    P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
    P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation

    //P4 Pin 3
    P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
    P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation

    //P4 Pin 4
    P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
    P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
    P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
    P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output

    //P4 Pin 5
    P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
    P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation

    //P4 Pin 6
    P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
    P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation

    //P4 Pin 7
    P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
    P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
    //------------------------------------------------------------------------------
}

void Init_Port5(void)
{ // Configure Port 5
    //------------------------------------------------------------------------------
    P5DIR = 0x00; // Set P1 direction to input
    P5OUT = 0x00; // P1 set Low

    P5SELC |= V_BAT; // ADC input for V_BAT

    P5SELC |= V_5_0; // ADC input for V_BAT

    P5SELC |= V_DAC; // ADC input for V_DAC

    P5SELC |= V_3_3; // ADC input for V_3_3

    P5SEL0 &= ~IOT_BOOT; // IOT_BOOT GPIO operation
    P5SEL1 &= ~IOT_BOOT; // IOT_BOOT GPIO operation
    P5OUT |= IOT_BOOT; // Set Output value inactive
    P5DIR |= IOT_BOOT; // Set direction to output
}

void Init_Port6(void)
{ // Configure Port 6
    //------------------------------------------------------------------------------
    P6OUT = 0x00; // P6 set Low
    P6DIR = 0x00; // Set P6 direction to output

    //P6 pin 0
    P6SEL0 |= LCD_BACKLITE;
    P6SEL1 &= ~LCD_BACKLITE;
    P6DIR |= LCD_BACKLITE;

    //P1 pin 1
    P6SEL0 |= R_FORWARD;
    P6SEL1 &= ~R_FORWARD;
    P6DIR |= R_FORWARD;

    //P6 pin 2
    P6SEL0 |= L_FORWARD;
    P6SEL1 &= ~L_FORWARD;
    P6DIR |= L_FORWARD;

    //P6 pin 3
    P6SEL0 |= R_REVERSE;
    P6SEL1 &= ~R_REVERSE;
    P6DIR |= R_REVERSE;

    //P6 pin 4
    P6SEL0 |= L_REVERSE;
    P6SEL1 &= ~L_REVERSE;
    P6DIR |= L_REVERSE;

    //P6 pin 5
    P6SEL0 &= ~P6_5;
    P6SEL1 &= ~P6_5;
    P6OUT &= ~P6_5;
    P6DIR |= P6_5;

    //P6 pin 6
    P6SEL0 &= ~GRN_LED;
    P6SEL1 &= ~GRN_LED;
    P6OUT &= ~GRN_LED;
    P6DIR |= GRN_LED;

    //------------------------------------------------------------------------------
}

