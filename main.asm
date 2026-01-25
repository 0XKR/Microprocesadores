;
; PRACTICA 2 MICROP.asm
;
; Created: 25/1/2026 7:46:46 a. m.
; Author : LENOVO T450
;
.INCLUDE "m328PDEF.INC"
.ORG 0
.CSEG

LDI R16, 0
LDI R17, 255
LDI R18, 4
LDI R19, 3

OUT DDRD, R16 ; puerto D entrada
OUT PORTD, R18 ; activar pullup en PD2 
OUT DDRB, R17 ; puerto B salida
OUT PORTB, R16 ; valor inicial cero

STS EICRA, R19 ; confg INT0 en flanco ascendente
SBI EIMSK, INT0 ; habilitar INT0
CBI EIFR, INTF0 ; borrar banderas de interrupcion
SEI ; habilitar interrupciones globales




