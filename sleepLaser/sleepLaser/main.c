/*
 * gerenciamentoEnergia.c
 *
 * Created: 02/05/2024 20:02:32
 * Author : 20232ewbj0262
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>


int main(void){
	DDRB |= (1<<5);
	DDRD |= (1<<7);
	PORTB &= ~(1<<5);
	sei();
    while (1) {
		// Configura o modo de sono como SLEEP_MODE_DOWN
		set_sleep_mode(SLEEP_MODE_STANDBY);
		
		//Habilita o modo de sono
		sleep_enable();
		
		//
		EIMSK |= (1<<INT0);
		// configura o bit ISC00 e ISC01 para borda de subida
		EICRA |= (1<<ISC00) | (1<<ISC01);
		
		/*PORTD |= (1<<7);
		_delay_ms(1000);
		PORTD &= ~(1<<7);
		_delay_ms(1000);*/
		
		// dorme at? que uma interrup??o ocorra
		sleep_cpu();
	}
}

ISR(INT0_vect){
	PORTB^=(1<<5);
	_delay_ms(1000);
}

