/**
 * @file   board_config.h
 * @Author Nicolas Jeker (n.jeker@gmx.net)
 * @date   January 2014
 * @brief  Configuration file (exclusive config bits).
 *
 * This file contains all necessary configuration (except the config bits)
 * to initialize a PIC18 microcontroller on the Ascom Picboard 5 (PBA5).
 */

#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

// === Defines =================================================================
#define USE_LCD
#define STDOUT_LCD true
//#define LCD_DEBUG_ON    // Shows state and loopdelay time (overflow) on lcd
#define USE_ADC

#define USE_LOOPDELAY_TIMER2
//#define USE_LOOPDELAY_TIMER0

#define ENABLE_INTERRUPTS
#define USE_RAND        // USE:  x = rand()%8+1; -> 1 bis 8 (%Breite+Offset)
                        // stdlib.h will be included and srand for init
// Define clock speed
#define _XTAL_FREQ 20000000 // 20 MHz



// === Compiler Commands =======================================================
#pragma jis // Extended string handling (special chars)



// === Includes ================================================================
#include <xc.h>
#include <stdio.h>
#include <string.h>

#include "config_18F4685.h" // Config bits
#include "peripheral.h"     // Peripherals Defines
#include "lcd.h"
#include "loopdelay.h"
#include "state_machine.h"

#ifdef USE_RAND
    #include <stdlib.h>
#endif



// === Typedefs ================================================================
typedef bit			BOOL;
typedef bit			BOOLEAN;
typedef unsigned char 		UINT8;
typedef unsigned int 		UINT16;
typedef unsigned short long 	UINT24;
typedef unsigned long		UINT32;
typedef signed char 		SINT8;
typedef signed int 		SINT16;
typedef signed short long 	SINT24;
typedef signed long		SINT32;



// === Prototypes ==============================================================
void init(void);
void putch(unsigned char c);
// _BOARD_CONFIG_H
#endif