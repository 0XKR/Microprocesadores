/*
 * Parcial 3 Gio Oscar.c
 *
 * Created: 17/3/2026 12:09:04 a. m.
 * Author : LENOVO T450
 */ 

#include "lcd.h"
#include <avr/interrupt.h>
#include <stdio.h>

// Definiciones de Hardware
#define PIN_SWITCH PC3
#define LED_AZUL   PD2
#define LED_AMAR   PD4
#define LED_VERDE  PD7
#define MOTOR_PWM  PD6  // Salida OC0A del Timer 0

volatile uint16_t adc_val = 0;
volatile uint8_t adc_ready = 0;

// Configuración ADC con interrupción ADIE
void setup_adc() {
	// Referencia AVCC, Canal inicial ADC0
	ADMUX = (1 << REFS0);
	// Habilitar ADC, Interrupción y Prescaler de 128 (16MHz/128 = 125kHz)
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

// Vector de Interrupción del ADC
ISR(ADC_vect) {
	adc_val = ADC;
	adc_ready = 1;
}

// Configuración Timer 0 para PWM de 7.8 kHz
void setup_timer0() {
	DDRD |= (1 << MOTOR_PWM);
	// Fast PWM, Non-Inverting
	TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
	// Prescaler 8: F = 16MHz / (8 * 256) = 7812.5 Hz
	TCCR0B = (1 << CS01);
	OCR0A = 0; // Iniciar apagado
}

int main(void) {
	char buffer[17];
	char str_aux[10]; // Buffer auxiliar para convertir los floats
	
	// Configuración de pines de entrada y LEDs
	DDRC &= ~(1 << PIN_SWITCH); // PC3 como entrada
	PORTC |= (1 << PIN_SWITCH); // Pull-up activo
	DDRD |= (1 << LED_AZUL) | (1 << LED_AMAR) | (1 << LED_VERDE);
	
	lcd_init();
	setup_adc();
	setup_timer0();
	sei(); // Habilitar interrupciones globales

	while (1) {
		// --- MODO MANUAL (Switch en LOW / 0) ---
		if (!(PINC & (1 << PIN_SWITCH))) {
			ADMUX = (ADMUX & 0xF0) | 0; // Canal ADC0 (Potenciómetro)
			ADCSRA |= (1 << ADSC);
			while(!adc_ready); adc_ready = 0;

			float voltaje = (adc_val * 5.0) / 1023.0;
			OCR0A = adc_val / 4;

			// Apagar LEDs en modo manual
			PORTD &= ~((1 << LED_AZUL) | (1 << LED_AMAR) | (1 << LED_VERDE));
			
			// Convertir voltaje a string (4 espacios total, 2 decimales)
			dtostrf(voltaje, 4, 2, str_aux);
			sprintf(buffer, "Pot: %s V      ", str_aux);
			
			lcd_gotoxy(0, 0);
			lcd_string(buffer);
		}
		// --- MODO AUTOMÁTICO (Switch en HIGH / 1) ---
		else {
			ADMUX = (ADMUX & 0xF0) | 1; // Canal ADC1 (LM35)
			ADCSRA |= (1 << ADSC);
			while(!adc_ready); adc_ready = 0;

			float temp = (adc_val * 500.0) / 1023.0;

			if (temp <= 22.0) {
				OCR0A = 0;
				// Encender Azul, apagar los otros (manteniendo PD6/PWM y PD0,1)
				PORTD = (PORTD & 0x63) | (1 << LED_AZUL);
				} else if (temp < 32.0) {
				OCR0A = 127; // 50%
				PORTD = (PORTD & 0x63) | (1 << LED_AMAR);
				} else {
				OCR0A = 242; // 95%
				PORTD = (PORTD & 0x63) | (1 << LED_VERDE);
			}

			// Convertir temperatura a string (4 espacios total, 1 decimal)
			dtostrf(temp, 4, 1, str_aux);
			sprintf(buffer, "Temp: %s C     ", str_aux);
			
			lcd_gotoxy(0, 0);
			lcd_string(buffer);
		}

		// --- Línea 2: Ciclo Útil (Entero, no necesita dtostrf) ---
		int duty = (int)((OCR0A * 100.0) / 255.0);
		sprintf(buffer, "Ciclo: %d%%      ", duty);
		
		lcd_gotoxy(0, 1);
		lcd_string(buffer);

		_delay_ms(150);
	}
}