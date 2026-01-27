;
; PRACTICA 2 MICROP.asm
;
; Created: 25/1/2026 7:46:46 a. m.
; Author : LENOVO T450
;
.INCLUDE "m328PDEF.INC"
.ORG 0
.CSEG

MAIN:

	LDI R16, 0
	LDI R17, 255
	LDI R18, 12
	LDI R19, 3

	OUT DDRD, R16 ; puerto D entrada
	OUT PORTD, R18 ; activar pullup en PD2 ; y PD3
	OUT DDRB, R17 ; puerto B salida
	OUT PORTB, R16 ; valor inicial cero

	STS EICRA, R19 ; confg INT0 en flanco ascendente
	SBI EIMSK, INT0 ; habilitar INT0

	CBI EIFR, INTF0 ; borrar banderas de interrupcion
	SEI ; habilitar interrupciones globales

ISR_INT0:

RETARDO:
	LDI R22, 8
I1:	
	LDI R23, 255
I2:
	LDI R24, 255
I3:
	DEC R24
	BRNE I3
	DEC R23
	BRNE I2
	DEC R22
	BRNE I1
	RET
	




