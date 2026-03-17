#define F_CPU 16000000UL
#include "lcd.h"
#include <stdlib.h>   // para dtostrf e itoa

int main(void) {
	int valor_entero =2026;
	float valor_float = 13.14159;
	char buffer[16];

	lcd_init();

	// Mostrar entero.  puede ser negativo tabien
	lcd_gotoxy(0, 0); // columna 0, linea 0 (home) de la pantalla de 16 columnas por linea
	lcd_string("ENTERO: ");// palabra a imprimir
	lcd_int(valor_entero); 

	// Mostrar float
	lcd_gotoxy(0, 1);// columna 0, linea 1
	lcd_string("Float: ");
	dtostrf(valor_float, 1, 3, buffer);  // convierte valor_float a 2 decimales y lo guarda 
	// en la variable buffer tipo char para poder mostrar en la lcd
	lcd_string(buffer);

	while (1);
}