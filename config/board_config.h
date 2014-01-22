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

// Include standard libraries

#include <xc.h>
#include "config_18F4685.h" // Config bits
#include <stdio.h>
#include <string.h>

// Include other libraries



// Define clock speed
#define _XTAL_FREQ 20000000 // 20 MHz
// Extended string handling (special chars)
#pragma jis




// Function prototypes

void init(void);

// _BOARD_CONFIG_H
#endif