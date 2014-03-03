/* 
 * File:   loopdelay.c
 * Author: Roger
 *
 * Created on 9. Februar 2014, 21:05
 */

#include "board_config.h"
#include "loopdelay.h"
#include <xc.h>


// === Loopdelay Time Set ===========================================================


static volatile unsigned int loopdelay_counter = 0;

void loopdelay(void){
    while(loopdelay_counter < loopdelay_time_ms);
    loopdelay_counter = 0;
}

void interrupt Global_ISR(void){
    if (TMR2IF && TMR2IE) {
        loopdelay_counter++;
        TMR2IF = 0;
        if(loopdelay_counter > loopdelay_time_ms){
            printf("\nLoopdelay Stuck");
        }
    }
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
