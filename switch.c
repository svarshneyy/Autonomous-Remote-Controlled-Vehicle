//------------------------------------------------------------------------------

//  Description: Contains interrupt configurations for switches 1 and 2,
//  and functions that process what each switch does.

//  Sanchit Varshney
//  Sep 2024
//  Built with Code Composer Version: 12.8

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  <string.h>
#include  "macros.h"


unsigned volatile int switch1_status;
unsigned volatile int switch2_status;
unsigned volatile int caliStatus;

extern unsigned volatile int debounce_count1;
extern unsigned volatile int debounce_count2;
extern unsigned char state;
unsigned int IRstatus = 0;
extern volatile unsigned char display_changed;
extern char display_line[4][11];
unsigned int blackLine;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
extern volatile unsigned int ADC_Thumb;




void Switch_Process(void){          // Calls SW1 and SW2 process functions
    Switch1_Process();
    Switch2_Process();
}

void Switch1_Process(void){         // Processes SW1
    if (switch1_status == PRESSED){
        if((state == MAIN) && !caliStatus) state = CALIBRATE;
        else state = MAIN;
    }
    switch1_status = RELEASED;
}

void Switch2_Process(void){         // Processes SW2
    if (switch2_status == PRESSED){
        if (state == CALIBRATE) {
            blackLine = (ADC_Left_Detect + ADC_Right_Detect) >> 1;
            caliStatus = 1;

        }
    }
    switch2_status = RELEASED;
}

#pragma vector=PORT4_VECTOR         // Interrupt configuration for SW1 (debounce).
__interrupt void switchP4_interrupt(void){

    if (P4IFG & SW1) {
        P4IE &= ~SW1;                   // Disable Switch 1 interrupt
        P4IFG &= ~SW1;                  // Clear interrupt flag
        TB0CCTL1 &= ~CCIFG;             // Clear the CCR1 interrupt flag
        TB0CCR1 = TB0CCR1_INTERVAL;     // Add Interval to TB0R for TB0CCR1
        TB0CCTL1 |= CCIE;               // Enable CCR1 interrupt

        //DO WHATEVER SW1 NEEDS TO DO:

        //TB0CCTL0 &= ~CCIE;              // Disable Time B0
        //P6OUT &= ~LCD_BACKLITE;         // Turn OFF backlight
        switch1_status = PRESSED;

    }
}


#pragma vector=PORT2_VECTOR             // // Interrupt configuration for SW2 (debounce).
__interrupt void switchP2_interrupt(void){
    //Switch 2
    if (P2IFG & SW2) {
        P2IE &= ~SW2;                   // Disable Switch 1 interrupt
        P2IFG &= ~SW2;                  // Clear interrupt flag
        TB0CCTL2 &= ~CCIFG;             // Clear the CCR1 interrupt flag
        TB0CCR2 = TB0CCR2_INTERVAL;     // Add Interval to TB0R for TB0CCR1
        TB0CCTL2 |= CCIE;               // Enable CCR1 interrupt

        //DO WHATEVER SW2 NEEDS TO DO:

        //TB0CCTL0 &= ~CCIE;
        //P6OUT &= ~LCD_BACKLITE;         // Turn OFF backlight
        switch2_status = PRESSED;

    }
}

