/*
 * LDR_BUZZER_LASER.c
 *
 * Created: 12/04/2024 20:34:17
 * Author : Pedro Victor
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int estouro = 0;
int segundos = 0;
int digitos[2];

int main(void){
	cli(); // desabilita a interrup??o global
	TCNT0 = 0; //registrador que armazena o valaor atual da contagem
	TCCR0B = (1<<CS02); // PRESCALE DE 1:256
	TIMSK0 = (1<<TOIE0); //Habilita a interrup??o por estouro
	sei(); //Habilita as interrup??es gerais
	DDRD = 0b11111111;
	DDRB = 0b00001111;
	PORTD = 0;
	PORTB = 0;
	
	while(1){}
}

void escreveDigitos(int numero, int array[]) {
	for (int i = 2 - 1; i >= 0; i--) {
		array[i] = numero % 10;
		numero /= 10;
	}
	PORTB = digitos[1];
	PORTD = digitos[0];
}

ISR(TIMER0_OVF_vect){
	estouro++;
	if(estouro==248){
		estouro=0;
		if(segundos > 60){
			segundos = 0;
			PORTB = segundos;
			PORTD = segundos;
		}else{
			escreveDigitos(segundos, digitos);
		}
		segundos++;
	}
}
