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


void putch(unsigned char c) {
#ifdef STDOUT_LCD
	lcd_putc(c);
#endif
}

void init(void)
{
// === PORT INITS ==============================================================
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

// === A/D Converter ===========================================================
#ifdef USE_ADC
    ADCON0 = 0x01; 	// Enable A/D Converter
    ADCON1 = 0x0D; 	// AN0 and AN1 = Analoge Pins
    ADCON2 = 0x24; 	// Left Adjustet, 8 TAD Time, FOSC/4
#else
    ADCON0 = 0x00;	// Disable A/D Converter
    ADCON1 = 0x0F;
    ADCON2 = 0x00;
#endif

// === LCD =====================================================================
#ifdef USE_LCD
    lcd_init();
#endif

// === LOOPDELAY TIMER2 ========================================================
#ifdef USE_LOOPDELAY_TIMER2
    // Creates every ms an Intterupt
    T2CON = 0b00101101; // bit 6-3  Postscale = 5
                        // bit 2    Timer On
                        // bit 1-0  Prescaler = 4
    PR2 = 250;

    // Interrupt:
    TMR2IE = 1; // Timer 2 Interrupt Enable
    TMR2IP = 1; // Priority Setting, Only Required wenn IPEN = 1
    //(Then only high priority interrupts (1) will be detected)
#endif
#ifdef USE_LOOPDELAY_TIMER0
	T0CON = 0b11000111; // bit 7	Timer On
						// bit 6	8-bit Mode
						// bit 5	Internal clock source (fosc/4)
						// bit 4	Source Edge (doesn't matter)
						// bit 3	Prescaler is enabled
						// bit 2-0	Prescaler = 256
	
    // Interrupt:
    TMR0IE = 1; // Timer 0 Interrupt Enable
    TMR0IP = 1; // Priority Setting, Only Required wenn IPEN = 1
    //(Then only high priority interrupts (1) will be detected)
#endif
#ifdef ENABLE_INTERRUPTS
    GIE = 1; // Global Interrupt Enable
    PEIE = 1; // Peripheral Interrupt Enable
#endif
}