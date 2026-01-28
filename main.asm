;
; PRACTICA 2 MICROP.asm
;
; Created: 25/1/2026 7:46:46 a. m.
; Author : LENOVO T450
;
.INCLUDE "m328PDEF.INC"
.ORG 0
	RJMP MAIN
.ORG 2
    RJMP ISR_INT0
.CSEG

MAIN:


	LDI R16, 0
	LDI R17, 255
	LDI R18, 0B00100100
	LDI R19, 3

	OUT DDRD, R16 ; puerto D entrada
	OUT PORTD, R18 ; activar pullup en PD2 ; y PD5
	OUT DDRB, R17 ; puerto B salida
	OUT PORTB, R16 ; valor inicial cero ///////////

	STS EICRA, R19 ; confg INT0 en flanco ascendente
	SBI EIMSK, INT0 ; habilitar INT0

	CBI EIFR, INTF0 ; borrar banderas de interrupcion
	SEI ; habilitar interrupciones globales

ESPERAR:
	RJMP ESPERAR

ISR_INT0:

ALARMA:
	LDI R20, 0B00100001
    OUT PORTB, R20      ; Encender LED y Buzzer
    RCALL RETARDO   ; Esperar 100ms
	
	SBIS PIND, PD5 ; SALTA SI EL BOTON DE SALIR ESTA ON
	RJMP SALIR_ALARMA 

    
    LDI R20, 0
    OUT PORTB, R20      ; Apagar LED y Buzzer
    RCALL RETARDO   ; Esperar 
	SBIS PIND, PD5
	RJMP SALIR_ALARMA
	RJMP ALARMA

SALIR_ALARMA:
	LDI R21, 0; ASEGURA QUE SE APAGUE LA ALARMA
	OUT PORTB, R21
	RCALL RETARDO
	RETI


RETARDO:
	LDI R22, 8 ; retardo de 100ms
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
	




