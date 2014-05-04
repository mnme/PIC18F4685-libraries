/* 
 * File:   main.c
 * Author: 
 *
 * Created on 
 */

typedef enum {  } TState;
TState state = ;

#include "config/board_config.h"


void main(void){
    init();
    state_machine_init(&state);
    loopdelay_time_ms = 10;
    
    
    
    while(1){
        loopdelay(state);
        get_events();
        switch(state){
            case :
                
                break;
            
        }
    }
}