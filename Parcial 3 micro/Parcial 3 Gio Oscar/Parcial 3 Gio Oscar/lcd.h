#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

// Control
#define LCD_RS_PORT  PORTB
#define LCD_RS_DDR   DDRB
#define LCD_RS_PIN   PB4

#define LCD_EN_PORT  PORTB
#define LCD_EN_DDR   DDRB
#define LCD_EN_PIN   PB5

// Datos (D4-D7 de la LCD van a PB0-PB3 del AVR)
#define LCD_D0_PORT  PORTB
#define LCD_D0_DDR   DDRB
#define LCD_D0_PIN   PB0

#define LCD_D1_PORT  PORTB
#define LCD_D1_DDR   DDRB
#define LCD_D1_PIN   PB1

#define LCD_D2_PORT  PORTB
#define LCD_D2_DDR   DDRB
#define LCD_D2_PIN   PB2

#define LCD_D3_PORT  PORTB
#define LCD_D3_DDR   DDRB
#define LCD_D3_PIN   PB3

void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_string(char *str);
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_clear(void);
#endif