#include "lcd.h"
#include <stdio.h>   // para dtostrf (aunque ya está en stdlib.h, pero a veces se necesita)

// Macros para control
#define RS_HIGH()   (LCD_RS_PORT |= (1 << LCD_RS_PIN))
#define RS_LOW()    (LCD_RS_PORT &= ~(1 << LCD_RS_PIN))
#define EN_HIGH()   (LCD_EN_PORT |= (1 << LCD_EN_PIN))
#define EN_LOW()    (LCD_EN_PORT &= ~(1 << LCD_EN_PIN))

// Macros para datos (D0-D3)
#define D0_HIGH()   (LCD_D0_PORT |= (1 << LCD_D0_PIN))
#define D0_LOW()    (LCD_D0_PORT &= ~(1 << LCD_D0_PIN))
#define D1_HIGH()   (LCD_D1_PORT |= (1 << LCD_D1_PIN))
#define D1_LOW()    (LCD_D1_PORT &= ~(1 << LCD_D1_PIN))
#define D2_HIGH()   (LCD_D2_PORT |= (1 << LCD_D2_PIN))
#define D2_LOW()    (LCD_D2_PORT &= ~(1 << LCD_D2_PIN))
#define D3_HIGH()   (LCD_D3_PORT |= (1 << LCD_D3_PIN))
#define D3_LOW()    (LCD_D3_PORT &= ~(1 << LCD_D3_PIN))

// Configurar todos los pines como salidas
static void lcd_pins_output(void) {
	LCD_RS_DDR  |= (1 << LCD_RS_PIN);
	LCD_EN_DDR  |= (1 << LCD_EN_PIN);
	LCD_D0_DDR  |= (1 << LCD_D0_PIN);
	LCD_D1_DDR  |= (1 << LCD_D1_PIN);
	LCD_D2_DDR  |= (1 << LCD_D2_PIN);
	LCD_D3_DDR  |= (1 << LCD_D3_PIN);
}

// Escribe un nibble (4 bits) en los pines D0-D3 y genera el pulso de enable
static void lcd_write_nibble(uint8_t nibble, uint8_t rs) {
	// RS
	if (rs) RS_HIGH();
	else    RS_LOW();

	// Colocar los 4 bits (nibble) en los pines D0-D3
	if (nibble & 0x01) D0_HIGH(); else D0_LOW();
	if (nibble & 0x02) D1_HIGH(); else D1_LOW();
	if (nibble & 0x04) D2_HIGH(); else D2_LOW();
	if (nibble & 0x08) D3_HIGH(); else D3_LOW();

	// Pulso de enable
	EN_HIGH();
	_delay_us(1);
	EN_LOW();
	_delay_us(1);
}

// Escribe un byte completo (2 nibbles) con el modo RS especificado
static void lcd_write_byte(uint8_t byte, uint8_t rs) {
	lcd_write_nibble(byte >> 4, rs);   // nibble alto
	lcd_write_nibble(byte & 0x0F, rs); // nibble bajo
}

// Envía un comando al LCD (RS = 0)
void lcd_command(uint8_t cmd) {
	lcd_write_byte(cmd, 0);
	_delay_us(2000);
}

// Envía un dato (carácter) al LCD (RS = 1)
void lcd_data(uint8_t data) {
	lcd_write_byte(data, 1);
	_delay_us(50);
}

// Inicializa el LCD
void lcd_init(void) {
	_delay_ms(50);                // Esperar estabilización

	lcd_pins_output();
	RS_LOW();
	EN_LOW();
	D0_LOW(); D1_LOW(); D2_LOW(); D3_LOW();

	// Secuencia de inicialización en modo 8 bits
	lcd_write_nibble(0x03, 0);
	_delay_ms(5);
	lcd_write_nibble(0x03, 0);
	_delay_us(150);
	lcd_write_nibble(0x03, 0);
	_delay_us(150);
	// Cambiar a modo 4 bits
	lcd_write_nibble(0x02, 0);
	_delay_us(150);

	// Configurar el LCD
	lcd_command(0x28);   // 4-bit, 2 líneas, 5x8
	lcd_command(0x08);   // display off
	lcd_command(0x01);   // clear
	_delay_ms(2);
	lcd_command(0x06);   // entry mode
	lcd_command(0x0C);   // display on, cursor off
}

// Posiciona el cursor (x: 0-15, y: 0-1)
void lcd_gotoxy(uint8_t x, uint8_t y) {
	uint8_t addr = (y == 0) ? (0x00 + x) : (0x40 + x);
	lcd_command(0x80 | addr);
}

// Borra la pantalla
void lcd_clear(void) {
	lcd_command(0x01);
	_delay_ms(2);
}

// Muestra una cadena
void lcd_string(char *str) {
	while (*str) {
		lcd_data(*str++);
	}
}

// Muestra un entero con signo
void lcd_int(int16_t num) {
	char buffer[7];
	itoa(num, buffer, 10);
	lcd_string(buffer);
}

// Muestra un entero sin signo
void lcd_uint(uint16_t num) {
	char buffer[6];
	utoa(num, buffer, 10);
	lcd_string(buffer);
}
// muestra decimales con 2 digitos decimales
void lcd_float(float num, uint8_t decimales) {
	char buffer[16];  // Suficiente para float con signo y decimales
	dtostrf(num, 1, decimales, buffer); // ancho mínimo 1, decimales indicados
	lcd_string(buffer);
}