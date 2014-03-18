/* 
 * File:   main.c
 * Author: Roger Germann
 *
 * Created on 27.02.14
 */



typedef enum {S_Status_1, S_Status_2, S_Status_3} TState;
TState state = S_Status_1;

#include "board_config.h"
#include <xc.h>
#define _XTAL_FREQ 20000000


volatile unsigned int loopdelay_time_ms = 10;

void main(void){
    init();
    state_machine_init(&state);

    printf("Hello World I am \nHappy");
    LED(0x01);

    while(1){
        loopdelay(); // Wartet loopdelay_time_ms lang
        get_events(); // Flags der Taster aktualisieren, Time_ms erhöhen/löschen
        switch(state){
            case S_Status_1:
                LED(adc_get_8bit());
//                if(Events.posEdge.switch0){
//                    LED(0x02);
//                    state = S_Status_2;
//                }
                break;
            case S_Status_2:
                if(Events.timeout_ms(200)){
                    LED9 ^=1;
                }
                if(Events.posEdge.switch0){
                    LED(0x01);
                    state = S_Status_1;
                }
                if(Events.posEdge.switch1){
                    LED(0x3FF);
                }
                break;
            case S_Status_3:
                break;
        }//end switch
    }//end while
}//end main





