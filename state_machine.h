/* 
 * File:   state_machine.h
 * Author: Roger
 *
 * Created on 9. Februar 2014, 21:05
 */

#ifndef STATE_MACHINE_H
#define	STATE_MACHINE_H

#include "board_config.h"

#ifndef USE_LOOPDELAY_TIMER2
    #error "Loopdelay not activated"
#endif

typedef struct {
    unsigned switch0: 1;
    unsigned switch1: 1;
    unsigned switch2: 1;
    unsigned switch3: 1;
    unsigned switch4: 1;
    unsigned switch5: 1;
    unsigned switch6: 1;
    unsigned switch7: 1;
}TTasterByte;


typedef struct {
    union
    {
        unsigned int value;
        struct
        {
            TTasterByte posEdge;
            TTasterByte negEdge;
        };
    };
    unsigned char (* timeout_once)(unsigned int);
    unsigned char (* timeout_ms)(unsigned int);
    unsigned char (* active_until_ms)(unsigned int);
    
    unsigned long time_ms;
    unsigned char f_state;  // A flag for state to check if the state has changed
} TEvents;

extern TEvents Events;

TEvents get_events(void);
void state_machine_init(void *s);
static unsigned char active_until_ms(unsigned int t);
static unsigned char timeout_ms(unsigned int t);
static unsigned char timeout_once_ms(unsigned int t);


// void loopdelay_handler(void);
// If you use interrupt in your main, uncomment this and the function in loopdelay.c
// put the handler into the interrupt in your main.

#endif	/* LOOPDELAY_H */

