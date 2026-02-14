
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int8_t cont;
int8_t band_final_carrera;
int8_t emerg;

int main(void)
{
	emerg = 0;
	cont = 0;
	DDRB = 3;
	DDRC = 0;
	DDRD = 0;
	PORTB = 0;
	PORTC = 1;
	PORTD = 0x04;
	TCNT0 = 100;
	TCCR0A = 0;
	TCCR0B = 0;
	TIMSK0 = 1;
    TIFR0 = 0;
	EICRA = 0x0E;
	EIMSK = 3;
	EIFR = 0;
	band_final_carrera = 0;
	sei();
	while(1){
		cont = 0;
		if(band_final_carrera == 1){
			if(PINC == 1){
				while(1){
					
					if(cont<=50){
						emerg=1;
						PORTB = 1;
						TCCR0B = 5;
					}
					else{
						PORTB = 0;
						emerg = 0;
						break;
					}
				}
				
			}
		}
	}
}

ISR(INT0_vect){
	
	if(emerg == 1){
		PORTB = 2;
		TCCR0B = 0;
		while(1){
			
		}
}}

ISR(INT1_vect){
	band_final_carrera = 1;
		
}

ISR(TIMER0_OVF_vect){
		
	cont++;
	TCNT0 = 100;
	PORTB = 0;
	TCCR0B = 0;
	band_final_carrera = 0;
			
}
