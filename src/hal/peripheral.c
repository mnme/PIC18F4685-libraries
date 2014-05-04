/* 
 * File:   peripheral.h
 * Author: Roger Germann
 *
 * Created on 9. Februar 2014, 20:20
 */

#include "peripheral.h"
#include "../config/board_config.h"

 #ifdef USE_ADC
 unsigned int adc_get_10bit(void){
    GODONE = 1;			//Wandlung starten (one shot)
    while(GODONE);
    return (((ADRESL>>6)&0x03) | (ADRESH << 2));
 }
 
 unsigned char adc_get_8bit(void){
    GODONE = 1;			//Wandlung starten (one shot)
    while(GODONE);
    return ADRESH;
 }
 
 void adc_set_channel(unsigned char channel){
    // CH_POTI1 oder CH_POTI2
    ADCON0 &= 0b11000011;
    ADCON0 |= ((channel&0b1111)<<2);
 }
 
 #endif