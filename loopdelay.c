/* 
 * File:   loopdelay.c
 * Author: Roger
 *
 * Created on 9. Februar 2014, 21:05
 */

#include "loopdelay.h"
#include <xc.h>


static volatile unsigned int loopdelay_counter = 0;

void interrupt Global_ISR(void){
    if (TMR2IF && TMR2IE) {
        loopdelay_counter++;
        TMR2IF = 0;
    }
}

void loopdelay_ms(unsigned int value){
    while(loopdelay_counter < value);
    loopdelay_counter = 0;
}
