//------------------------------------------------------------------------------

//  Description: Contains a function that configures all the initial conditions.

//  Sanchit Varshney
//  Sep 2024
//  Built with Code Composer Version: 12.8

//------------------------------------------------------------------------------


#include  "msp430.h"
#include  <string.h>
#include  "macros.h"


//variables
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern unsigned volatile int switch1_status;
extern unsigned volatile int switch2_status;
extern unsigned volatile int debounce_count1;
extern unsigned volatile int debounce_count2;
extern unsigned int character;
extern unsigned int currCharacter;
extern unsigned int line;
extern unsigned int nextline;
extern volatile unsigned int iot_rx_wr;
extern unsigned int iot_rx_rd;
extern unsigned int currentAT;
extern unsigned int boot_state;


void Init_Conditions(void){
//------------------------------------------------------------------------------

  int i;
  for(i=0;i<11;i++){
    display_line[0][i] = RESET_STATE;
    display_line[1][i] = RESET_STATE;
    display_line[2][i] = RESET_STATE;
    display_line[3][i] = RESET_STATE;
  }
  display_line[0][10] = 0;
  display_line[1][10] = 0;
  display_line[2][10] = 0;
  display_line[3][10] = 0;

  display[0] = &display_line[0][0];
  display[1] = &display_line[1][0];
  display[2] = &display_line[2][0];
  display[3] = &display_line[3][0];
  update_display = 0;


// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------

  switch1_status = RELEASED;
  switch2_status = RELEASED;
  debounce_count1 = DEBOUNCE_RESTART;
  debounce_count2 = DEBOUNCE_RESTART;
  line = 0;
  character = 0;
  currCharacter = 0;
  nextline = 0;
  iot_rx_wr = 0;
  iot_rx_rd = 0;
  currentAT = 0;
  boot_state = 0;


}
