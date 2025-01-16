//------------------------------------------------------------------------------

//  Description: Contains interrupt configurations for timers.

//  Sanchit Varshney
//  Oct 2024
//  Built with Code Composer Version: 12.8

//------------------------------------------------------------------------------


#include  "msp430.h"
#include  <string.h>
#include  "macros.h"


volatile unsigned int Time_Sequence;
volatile unsigned int Time_Sequence1;
extern volatile unsigned char update_display;
unsigned volatile int debounce_count1;
unsigned volatile int debounce_count2;
extern unsigned volatile int switch1_status;
extern unsigned volatile int switch2_status;
unsigned int secondCounter;
unsigned int displayCounter;
unsigned int moveTimer;
unsigned int seconds;
unsigned int pingCounter;
unsigned int ping;




#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
    //------------------------------------------------------------------------------
    // TimerB0 0 Interrupt handler (Triggers every 200 ms)
    //----------------------------------------------------------------------------

    // Time Sequence
    // Update display
    // secondCounter
    // pingCounter
    // moveTimer





    secondCounter++;
    if (secondCounter >= 10) {
        seconds++;
        secondCounter = 0;
    }

    moveTimer++;
    if (moveTimer >= 65000){
        moveTimer = 0;
        seconds = 0;
    }


    Time_Sequence++;
    if (Time_Sequence >= 65000){
        Time_Sequence = 0;
    }

    pingCounter++;
    if (pingCounter >= 50){
        ping = 1;
        pingCounter = 0;
    }

    displayCounter++;
    if (displayCounter >= 2){
        update_display = TRUE;
        displayCounter = 0;
    }



    //P6OUT ^= LCD_BACKLITE;
    TB0CCR0 += TB0CCR0_INTERVAL; // Add interval Offset to TACCR0
}

#pragma vector = TIMER0_B1_VECTOR           // Timer that triggers every 200 ms.
__interrupt void TIMER0_B1_ISR(void){
    //----------------------------------------------------------------------------
    // TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
    // Handles SW1 and SW2 debounce.
    //----------------------------------------------------------------------------
    switch(__even_in_range(TB0IV,14)){

    case 0: break; // No interrupt

    case 2: // CCR1 used
        debounce_count1++;
        if (debounce_count1 >= DEBOUNCE_TIME){
            debounce_count1 = DEBOUNCE_RESTART;             // Reset debounce

            TB0CCTL1 &= ~CCIE;                              // Disable CCR1 interrupt
            P4IFG &= ~SW1;                                  // Clear interrupt flag
            P4IE |= SW1;                                    // Re-enable Switch 1 interrupt
            switch1_status = RELEASED;

            //TB0CCTL0 |= CCIE;                             // Enable CCR0 interrupt
            //P6OUT |= LCD_BACKLITE;


        }
        TB0CCR1 += TB0CCR1_INTERVAL;                        // Add Offset to TBCCR1

        break;

    case 4: // CCR2 used
        debounce_count2++;
        if (debounce_count2 >= DEBOUNCE_TIME){
            debounce_count2 = DEBOUNCE_RESTART;             // Reset debounce

            TB0CCTL2 &= ~CCIE;                              // Disable CCR1 interrupt
            P2IFG &= ~SW2;                                  // Clear interrupt flag
            P2IE |= SW2;                                    // Re-enable Switch 1 interrupt
            switch2_status = RELEASED;

            //TB0CCTL0 |= CCIE;                             // Enable CCR0 interrupt
            //P6OUT |= LCD_BACKLITE;

        }
        TB0CCR2 += TB0CCR2_INTERVAL;                        // Add Offset to TBCCR2
        break;

    case 14: // overflow
        break;

    default: break;
    }
    //----------------------------------------------------------------------------
}


