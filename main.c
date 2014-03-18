/* 
 * File:   main.c
 * Author: Roger Germann
 *
 * Created on 27.02.14
 */



typedef enum {S_Set, S_Break, S_Game, S_End} TState;
TState state = S_Set;

#include "board_config.h"
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000


void main(void){
    init();
    state_machine_init(&state);

    loopdelay_time_ms = 10;

    unsigned int v_master, v_p1, v_p2;


    printf("\fMaster Set");

    
    while(1){
        loopdelay(state); // Wartet loopdelay_time_ms lang
        get_events(); // Flags der Taster aktualisieren, Time_ms erhöhen/löschen
        switch(state){
            // === S_Start =====================================================
            case S_Set:
                if(Events.posEdge.switch0){
                    v_master = adc_get_10bit();
                    printf("\fPlayer Set");
                    state = S_Game;
                }

                if(Events.timeout_ms(1000)){
                    LED0 = !LED0;
                }

                break;
            // === S_Break =====================================================
            case S_Break:

                break;
            // === S_Game ======================================================
            case S_Game:
                if(Events.posEdge.switch0){
                    v_p1 = adc_get_10bit();
                    adc_set_channel(CH_POTI2);
                    v_p2 = adc_get_10bit();
                    adc_set_channel(CH_POTI1);
                    if(v_p1 != v_p2){
                        printf("\fMaster: %4d\nP1:%4d  P2:%4d", v_master, v_p1, v_p2);
                        state = S_End;
                    }
                }
                break;
            // === S_End =======================================================
            case S_End:
                if(Events.timeout_ms(3000)){
                    if((v_master - v_p1) == (v_master - v_p2)){
                        printf("\fUnentschieden");
                    } else if (abs(v_master - v_p1) > abs(v_master - v_p2)){
                        printf("\fP2 Gewinnt");
                    } else {
                        printf("\fP1 Gewinnt");
                    }
                }

                if(Events.posEdge.switch0){
                    printf("\fMaster Set");
                    state = S_Set;
                }

                break;
            // === End State Machine ===========================================

        }//end switch
    }//end while
}//end main





