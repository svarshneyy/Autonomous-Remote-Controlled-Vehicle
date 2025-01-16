//------------------------------------------------------------------------------

//  Description: Contains #defines used throughout most source files.

//  Sanchit Varshney
//  Sep 2024
//  Built with Code Composer Version: 12.8

//------------------------------------------------------------------------------

#include "ports.h"
#include "LCD.h"
#include "functions.h"


#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define TRUE                 (0x01) //

#define NONE ('N')
#define FOLLOW ('F')
#define WAIT ('W')
#define IDLE ('I')
#define DETECT ('D')
#define STOP ('S')
#define ALIGN ('A')
#define END ('E')
#define DONE ('X')
#define TURN ('T')
#define CENTER ('C')

#define ONE ('1')
#define TWO ('2')
#define THREE ('3')
#define FOUR ('4')

#define BL_START ('1')
#define INTERCEPT ('2')
#define BL_TURN ('3')
#define BL_TRAVEL ('4')
#define BL_CIRCLE ('5')
#define BL_EXIT ('6')
#define BL_STOP ('5')

#define MAIN (0)
#define CALIBRATE (1)

#define WHEEL_COUNT_TIME (10)
#define RIGHT_COUNT_TIME (10)
#define LEFT_COUNT_TIME (10)
#define TRAVEL_DISTANCE (35)

#define WHEEL_COUNT_TIME_CIRCLE (15)
#define RIGHT_COUNT_TIME_CIRCLE (1)
#define LEFT_COUNT_TIME_CIRCLE (15)
#define TRAVEL_DISTANCE_CIRCLE (85)
#define TRAVEL_DISTANCE_CIRCLE_O (115)


#define WHEEL_COUNT_TIME_TRIANGLE1 (10)
#define RIGHT_COUNT_TIME_TRIANGLE1 (10)
#define LEFT_COUNT_TIME_TRIANGLE1 (10)
#define TRAVEL_DISTANCE_TRIANGLE1 (18)

#define WHEEL_COUNT_TIME_TRIANGLE2 (10)
#define RIGHT_COUNT_TIME_TRIANGLE2 (0)
#define LEFT_COUNT_TIME_TRIANGLE2 (10)
#define TRAVEL_DISTANCE_TRIANGLE2 (18)

#define WAITING2START (250)

#define PRESSED                (1)
#define RELEASED               (0)
#define NOT_OKAY               (0)
#define OKAY                   (1)
#define DEBOUNCE_TIME          (6)
#define DEBOUNCE_RESTART       (0)

#define P4PUD (P4OUT)
#define P2PUD (P2OUT)

#define TIMER_B0_CCRO_VECTOR            TIMERO_BO_VECTOR
#define TIMER_B0_CCR1_2_OV_VECTOR       TIMERO_B1_VECTOR
#define TIMER_B1_CCRO_VECTOR            TIMER1_B0_VECTOR
#define TIMER_B1_CCR1_2_OV_VECTOR       TIMER1_B1_VECTOR
#define TIMER_B2_CCRO_VECTOR            TIMER2_BO_VECTOR
#define TIMER_B2_CCR1_2_OV_VECTOR       TIMER2_B1_VECTOR
#define TIMER_B3_CCRO_VECTOR            TIMER3_B0_VECTOR
#define TIMER_B3_CCR1_2_OV_VECTOR       TIMER3_B1_VECTOR

#define TB0CCR0_INTERVAL        (12500) // 100 ms
#define TB0CCR1_INTERVAL        (25000) // 200 ms
#define TB0CCR2_INTERVAL        (25000) // 200 ms

#define TB3CCR0_INTERVAL        (5000) // 200 ms

#define PWM_PERIOD              (TB3CCR0)
#define LCD_BACKLITE_BRIGHTNESS (TB3CCR1)
#define RIGHT_FORWARD_SPEED     (TB3CCR2)
#define LEFT_FORWARD_SPEED      (TB3CCR3)
#define RIGHT_REVERSE_SPEED     (TB3CCR4)
#define LEFT_REVERSE_SPEED      (TB3CCR5)

#define SLOW (15000)
#define FAST (35000)
#define PERCENT_100 (50000)
#define PERCENT_80 (45000)
#define PWM_MODE               (0x01)
#define WHEEL_OFF              (0)
#define WHEEL_PERIOD          (50005)


#define BEGINNING (0)
#define SMALL_RING_SIZE (24)
#define PROCESS_SIZE (32)
#define LARGE_RING_SIZE (32)

