//------------------------------------------------------------------------------

//  Description: Contains a function that processes display updates.

//  Sanchit Varshney
//  Sep 2024
//  Built with Code Composer Version: 12.8

//------------------------------------------------------------------------------


#include  "msp430.h"
#include  <string.h>
#include  "macros.h"


//variables
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern unsigned char dispEvent;


void Display_Process(void){
    if(update_display){
        update_display = 0;
        if(display_changed){
            display_changed = 0;
            Display_Update(0,0,0,0);
        }
    }
}




