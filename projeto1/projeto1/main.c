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
int estado = 0;

int main(void){
	DDRB = 0b00001111;
	DDRD = 0b11110011;
	EICRA = 0b00001111; // Habilita interrupção por borda de subida INT0
	sei(); // habilita a chave geral de interrupção
	EIMSK = 0b00000011;
	PORTD |= (1<<1); // liga laser
	PORTD |= (1<<4); // liga rele
    while (1) {
		//PORTD |= (1<<6); //liga led verde
		//PORTD &= ~(1<<5); //desliga led vermelho
    }
}

ISR(INT0_vect){
	PORTB = c;
	c++;
	if(c > 9){
		PORTD |= (1<<7); // liga buzzer
		c = 0;
	}
}

ISR(INT1_vect){
	if(estado == 0){
		PORTD &= ~(1<<7); // desliga buzzer
		PORTD &= ~(1<<4); // desliga rele
		PORTD &= ~(1<<1); // desliga laser
		estado = !estado;
		PORTB = 0;
	}else{
		PORTD |= (1<<4); // liga rele
		PORTD |= (1<<1); // liga laser
		estado = !estado;
		PORTB = 0;
	}
}

