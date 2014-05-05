/* 
 * File:   main.c
 * Author: 
 *
 * Created on 
 */

#include "config/board_config.h"


void main(void){
    init();
    adc_set_channel(1);
    loopdelay_time_ms = 10;
    
    int adc = 0, adc_last = -1;
    
    while(1){
        loopdelay(0);
        PORTD = PORTB;
        adc = adc_get_10bit();
        if(adc != adc_last)
        {
            printf("\fADC: %04d", adc);
            adc_last = adc;
        }
    }
}