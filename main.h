/* 
 * File:   main.h
 * Author: StudElo01
 *
 * Created on 17. Januar 2014, 15:37
 */

#ifndef MAIN_H
#define	MAIN_H

// Haupt-Header-File des Compilers einbinden
#include <xc.h>
// Taktfrequenz definieren (wird für Loop-Delay benötigt)
#define _XTAL_FREQ 20000000

#include "io_library.h"



#define Taster0 RB0
#define Taster1 RB1
#define Taster2 RB2
#define Taster3 RB3
#define Taster4 RB4
#define Taster5 RB5
#define Taster6 RB6
#define Taster7 RB7
#define Taster PORTB

#define Led0 LATD0
#define Led1 LATD1
#define Led2 LATD2
#define Led3 LATD3
#define Led4 LATD4
#define Led5 LATD5
#define Led6 LATD6
#define Led7 LATD7
#define LED PORTD


#endif	/* MAIN_H */

