/*
 * timer.c
 *
 * Created: 26/04/2024 20:59:57
 * Author : 20232ewbj0262
 */ 

#define CPU_F 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

int counter;

int main(void){
	cli(); // desabilita a interrupção global
	DDRD |= (1<<0);
	PORTD &= ~(1<<0);
	TCNT0 = 0; //registrador que armazena o valaor atual da contagem
	TCCR0B = (1<<CS02); // PRESCALE DE 1:256
	TIMSK0 = (1<<TOIE0); //Habilita a interrupção por estouro
	sei(); //Habilita a iterrução global
	
    while (1) {}
}

ISR(TIMER0_OVF_vect){
	counter++;
	if(counter==488){
		PORTD^=(1<<0);
		counter=0;
	}
}

