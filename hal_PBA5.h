/* 
 * File:   hal.h
 * Author: Roger
 *
 * Created on 9. Februar 2014, 20:20
 */

#ifndef HAL_H
#define	HAL_H

// === TASTER ==================================================================
#define TASTER0 RB0
#define TASTER1 RB1
#define TASTER2 RB2
#define TASTER3 RB3
#define TASTER4 RB4
#define TASTER5 RB5
#define TASTER6 RB6
#define TASTER7 RB7
#define TASTER  PORTB


// === LED =====================================================================
#define LED0    LATD0
#define LED1    LATD1
#define LED2    LATD2
#define LED3    LATD3
#define LED4    LATD4
#define LED5    LATD5
#define LED6    LATD6
#define LED7    LATD7
#define LED8    LATE0
#define LED9    LATE1
#define LED(x)	(LATD = ((x)&0xFF)); (LATE = (((x)>>8)&0x03))


// === ADC =====================================================================
#define CH_POTI1
#define CH_POTI2
//adc_read(POTI1, 8bit)


// === LCD =====================================================================
#define LCD_RW  LATC0
#define LCD_EN  LATC1
#define LCD_RS  LATC2
#define LCD_D4  LATE2
#define LCD_D5  LATA2
#define LCD_D6  LATA4
#define LCD_D7  LATA5


// === OTHER ===================================================================
#define SUMMER  LATC5

#endif	/* HAL_H */

