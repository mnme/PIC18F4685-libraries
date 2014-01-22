/**
 * @file   board_config.c
 * @Author Nicolas Jeker (n.jeker@gmx.net)
 * @date   January 2014
 * @brief  Configuration file (exclusive config bits).
 *
 * This file contains all necessary configuration (except the config bits)
 * to initialize a PIC18 microcontroller on the Ascom Picboard 5 (PBA5).
 */
 
#include "board_config.h"

/**
 * @name	Init
 * @brief	Initializes I/Os and modules.
 * @ingroup	config
 * 
 * This method initializes 
 */
void init(void)
{
	TRISA = 0x03;
	TRISB = 0xFF; // Input switches
	TRISC = 0x80;
	TRISD = 0x00; // Output LEDs
	TRISE = 0x00; // Output LCD & LED 8,9
	
	// Reset outputs
	PORTA = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;
	
	// Disable A/D Converter
	ANCON0 = 0x00;
	ADCON1 = 0x0F;
	ADCON2 = 0x00;
}