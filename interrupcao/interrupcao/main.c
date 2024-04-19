/*
 * interrupcao.c
 *
 * Created: 18/04/2024 21:09:58
 * Author : 20232ewbj0262
 */ 

#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int c = 0;

int main(void){
	DDRB = 0b00001111;
	DDRD = 0b11100000;
	EICRA = 0b00000011; // Habilita interrupção por borda de subida INT0
	sei(); // habilita a chave geral de interrupção
	EIMSK = 0b00000001;
	
    while (1) {
		PORTD |= (1<<6); //liga led verde
		PORTD &= ~(1<<5); //desliga led vermelho
    }
}

ISR(INT0_vect){
	PORTD |= (1<<5); //liga led vermelho
	PORTD &= ~(1<<6); //desliga led verde
	_delay_ms(50);
	c++;
	if(c > 9){
		c = 0;
		PORTD |= (1<<7); // liga buzzer
		_delay_ms(2000); // espera 2s
		PORTD &= ~(1<<7); // desliga buzzer
	}
	PORTB = c;
}

