/* 
 * File:   main.c
 * Author: StudElo01
 *
 * Created on 17. Januar 2014, 15:37
 */

#define MAX_LOOP_DELAY_MS	10000
#define LOOPDELAY_TIME_MS   10

#include "board_config.h"
#include <xc.h>
#define _XTAL_FREQ 20000000

void interrupt Global_ISR(void);


#define 	time_ms_period(x)	(!(time_ms%x))
unsigned int time_ms = 0;

void main(void){
    init();

    unsigned int i = 0;
    while(1){
        loopdelay_ms(LOOPDELAY_TIME_MS);
        time_ms += LOOPDELAY_TIME_MS;

        if(time_ms_period(500)){
            i++;
            LED(i);
        }
    }//while
}//main





