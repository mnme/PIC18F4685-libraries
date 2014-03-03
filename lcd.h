/* 
 * File:   lcd.h
 * Author: Roger
 *
 * Created on 27. Februar 2014, 19:02
 */

#ifndef LCD_H
#define	LCD_H


#define CURSOR_ON           0x06
#define CURSOR_OFF          0x04
#define CURSOR_OFF_BLINK    0x05
#define CURSOR_ON_BLINK     0x07


//Makros für das Senden eines Befehl
#define lcd_send_command(command)	lcd_send(command)
//Makros für das Senden eines Datenbytes (Zeichen)
#define lcd_send_data(value)		LCD_RS=1;lcd_send(value);LCD_RS=0

void lcd_send(unsigned char value);
void lcd_clear(void);
void lcd_home(void);
void lcd_shle(unsigned char value);
void lcd_shri(unsigned char value);
void lcd_gotoxy(unsigned char dispx, unsigned char dispy);
void lcd_putc(char ch);
void lcd_puts(unsigned char *ptr);
void lcd_puts_rom(const unsigned char *ptr);
void lcd_curs(unsigned char c_mode);
void lcd_init(void);

#endif	/* LCD_H */

