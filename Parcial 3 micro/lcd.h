#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

// --------------------- CONFIGURACIÓN DE PINES (PORTB) ---------------------
// RS en PB4
#define LCD_RS_PORT  PORTB
#define LCD_RS_DDR   DDRB
#define LCD_RS_PIN   PB4

// EN en PB5
#define LCD_EN_PORT  PORTB
#define LCD_EN_DDR   DDRB
#define LCD_EN_PIN   PB5

// D0 (bit menos significativo del nibble) en PB0
#define LCD_D0_PORT  PORTB
#define LCD_D0_DDR   DDRB
#define LCD_D0_PIN   PB0

// D1 en PB1
#define LCD_D1_PORT  PORTB
#define LCD_D1_DDR   DDRB
#define LCD_D1_PIN   PB1

// D2 en PB2
#define LCD_D2_PORT  PORTB
#define LCD_D2_DDR   DDRB
#define LCD_D2_PIN   PB2

// D3 (bit más significativo) en PB3
#define LCD_D3_PORT  PORTB
#define LCD_D3_DDR   DDRB
#define LCD_D3_PIN   PB3

// --------------------------------------------------------------------------

// Funciones públicas
void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_string(char *str);
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_clear(void);
void lcd_int(int16_t num);
void lcd_uint(uint16_t num);

#endif
