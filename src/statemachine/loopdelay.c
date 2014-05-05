/* 
 * File:   loopdelay.c
 * Author: Roger Germann
 *
 * Created on 9. Februar 2014, 21:05
 */

#include "../config/board_config.h"
#include "loopdelay.h"


// === Loopdelay Time Set ===========================================================


static volatile unsigned int loopdelay_counter = 0;

static unsigned char stuck = 0;
void loopdelay(unsigned int value){
#ifdef LCD_DEBUG_ON
    printf("\fstate: %2d        ", value);
    if(stuck == 1){
        printf("\nTime:%3d  Stuck!", loopdelay_counter);
        stuck = 0;
    } else {
        printf("\nTime:%3d", loopdelay_counter);
    }
#endif
    while(loopdelay_counter < loopdelay_time_ms);
    loopdelay_counter = 0;
}

void interrupt Global_ISR(void){
#ifdef USE_LOOPDELAY_TIMER2
    if (TMR2IF && TMR2IE) {
        TMR2IF = 0;
        loopdelay_counter++;
        if(loopdelay_counter > loopdelay_time_ms){
            stuck = 1;  // Can't use printf here, takes too long!
        }
    }
#endif
#ifdef USE_LOOPDELAY_TIMER0
    if (TMR0IF && TMR0IE) {
        TMR0IF = 0;
        loopdelay_counter++;
        TMR0L = 100; // preload
        if(loopdelay_counter > loopdelay_time_ms){
            stuck = 1;  // Can't use printf here, takes too long!
        }
    }
#endif
}




/* If you use interrupt in your main, uncomment this and the prototyp in loopdelay.h 
   put the handler into the interrupt in your main.
void loopdelay_handler(void){
    if (TMR2IF && TMR2IE) {
        loopdelay_counter++;
		if(loopdelay_counter > LOOPDELAY_TIME){
			-> Program Blocked
		}
        TMR2IF = 0;
    }	
}
*/
