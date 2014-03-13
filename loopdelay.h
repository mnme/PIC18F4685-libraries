/* 
 * File:   loopdelay.h
 * Author: Roger Germann
 *
 * Created on 9. Februar 2014, 21:05
 */

#ifndef LOOPDELAY_H
#define	LOOPDELAY_H

extern volatile unsigned int loopdelay_time_ms;

void loopdelay(void);
void interrupt Global_ISR(void);

// void loopdelay_handler(void);
// If you use interrupt in your main, uncomment this and the function in loopdelay.c
// put the handler into the interrupt in your main.

#endif	/* LOOPDELAY_H */

