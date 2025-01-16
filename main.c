//------------------------------------------------------------------------------

//  Description: Contains the Main Routine - "While" Operating System.

//  Sanchit Varshney
//  Sep 2024
//  Built with Code Composer Version: 12.8

//------------------------------------------------------------------------------


#include  "msp430.h"
#include  <string.h>
#include  "macros.h"


// Global Variables
volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile unsigned int Time_Sequence1;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;
unsigned int wheel_move;
char forward;
char thousands;
char hundreds;
char tens;
char ones;
unsigned int Last_Time_Sequence; // a variable to identify Time_Sequence has changed
unsigned int cycle_time; // is a new time base used to control making shapes
unsigned int time_change; // is an identifier that a change has occurred
unsigned int backlight_status;
unsigned int cycle_time;
unsigned int time_change;
unsigned char state;
unsigned char event;
unsigned char currentDisplay;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
extern volatile unsigned int ADC_Thumb;
extern unsigned int timer_count;
extern unsigned int timer_count1;
extern unsigned int timer_count2;
unsigned int start_timer;
extern unsigned int ipLine;
extern unsigned int boot_state;
extern volatile unsigned char ip_address[17];
extern int ip_address_found;
extern volatile unsigned char IOT_Data[4][50];
unsigned int blackLine;




//void main(void){
void main(void){
    //    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //------------------------------------------------------------------------------
    // Main Program
    // This is the main routine for the program. Execution of code starts here.
    // The operating system is Back Ground Fore Ground.
    //
    //------------------------------------------------------------------------------
    PM5CTL0 &= ~LOCKLPM5;
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings

    Init_Ports();                        // Initialize Ports
    Init_Clocks();                       // Initialize Clock System
    Init_Conditions();                   // Initialize Variables and Initial Conditions
    Init_Timers();                       // Initialize Timers
    Init_LCD();                          // Initialize LCD
    Init_ADC();
    Init_Serial_UCA0(5);
    Init_Serial_UCA1(5);


    // Place the contents of what you want on the display, in between the quotes
    // Limited to 10 characters per line
    strcpy(display_line[0], "          ");
    strcpy(display_line[1], "          ");
    strcpy(display_line[2], "          ");
    strcpy(display_line[3], "          ");
    display_changed = TRUE;
    //  Display_Update(0,0,0,0);

    wheel_move = 0;
    forward = TRUE;


    //------------------------------------------------------------------------------
    // Begining of the "While" Operating System
    //------------------------------------------------------------------------------


    event = NONE;
    state = MAIN;
    currentDisplay = NONE;

    while(ALWAYS) {                         // Can the Operating system run

        Display_Process();                  // Update display
        Switch_Process();                   // Process switches
        Black_Line();                       // Follow black line
        IOT_Process();                      // Process IOT
        Sanchit_StateMachine();             // State machine processes

    }
}
//------------------------------------------------------------------------------

void Sanchit_StateMachine(void){            // State machine that allows for calibration
    if(boot_state){
        switch(state){
        case MAIN:
            break;

        case CALIBRATE:
            strcpy(display_line[0], "CALIBRATE ");
            strcpy(display_line[1], " R: 0000  ");
            strcpy(display_line[2], " L: 0000  ");
            strcpy(display_line[3], " B: 0000  ");

            HexToBCD(ADC_Left_Detect);
            adc_line(2,4);
            HexToBCD(ADC_Right_Detect);
            adc_line(3,4);
            HexToBCD(blackLine);
            adc_line(4,4);
            display_changed = TRUE;

            ip_address_found = 1;
            break;

        default: break;
        }
    }

}





