//------------------------------------------------------------------------------

//  Description: Contains functions for motor control; Includes pin updates and PWM.

//  Sanchit Varshney
//  Sep 2024
//  Built with Code Composer Version: 12.8

//------------------------------------------------------------------------------


#include  "msp430.h"
#include  <string.h>
#include  "macros.h"


void Forward_Off(void){         // Set pins to stop forward movement
    P6OUT  &=  ~R_FORWARD;
    P6OUT  &=  ~L_FORWARD;
}

void Reverse_Off(void){         // Set pins to stop backward movement
    P6OUT  &=  ~R_REVERSE;
    P6OUT  &=  ~L_REVERSE;
}

void Forward_On (void){         // Set pins to start forward movement
    P6OUT  |=  R_FORWARD;
    P6OUT  |=  L_FORWARD;
}

void Reverse_On (void){         // Set pins to start backward movement
    P6OUT  |=  R_REVERSE;
    P6OUT  |=  L_REVERSE;
}

void Motors_Off (void){         // Stop both forward and backward movement
    Forward_Off();
    Reverse_Off();
}

void motorCompare (void){       //Stop all movement if a motor is moving forward and backward at the same time
    if ((P6IN & L_FORWARD) && (P6IN & L_REVERSE)){
        P6OUT &= ~L_FORWARD;
        P6OUT &= ~L_REVERSE;
        P1OUT |= RED_LED;
    }
    if ((P6IN & R_FORWARD) && (P6IN & R_REVERSE)){
        P6OUT &= ~R_FORWARD;
        P6OUT &= ~R_REVERSE;
        P1OUT |= RED_LED;
    }
}

void PWM_LF_RF_LR_RR(char a, char b, char c, char d){   //Sets the speed for each motor, and the direction of movement

    switch(a){
    case 'o':
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        break;
    case 's':
        LEFT_FORWARD_SPEED = SLOW;
        break;
    case 'f':
        LEFT_FORWARD_SPEED = FAST;
        break;
    default:
        break;
    }

    switch(b){
    case 'o':
        RIGHT_FORWARD_SPEED = WHEEL_OFF;
        break;
    case 's':
        RIGHT_FORWARD_SPEED = SLOW;
        break;
    case 'f':
        RIGHT_FORWARD_SPEED = FAST;
        break;
    default:
        break;
    }

    switch(c){
    case 'o':
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        break;
    case 's':
        LEFT_REVERSE_SPEED = SLOW;
        break;
    case 'f':
        LEFT_REVERSE_SPEED = FAST;
        break;
    default:
        break;
    }

    switch(d){
    case 'o':
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        break;
    case 's':
        RIGHT_REVERSE_SPEED = SLOW;
        break;
    case 'f':
        RIGHT_REVERSE_SPEED = FAST;
        break;
    default:
        break;
    }

}







