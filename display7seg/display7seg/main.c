/*
 * LDR_BUZZER_LASER.c
 *
 * Created: 12/04/2024 20:34:17
 * Author : Pedro Victor
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

int main(void){
	DDRD = 0b00001111;
	DDRB = 0b00001111;
	PORTD = 0;
	int cont = 0;
	
	while(1){
		if(PINB&(1<<4)){ // verifica estado do ldr
			PORTB &= ~(1<<3); //desliga led verde
			PORTB |= (1<<2); //liga led vermelho
			cont++; 
			while(PINB&(1<<4)){}
			}else{
			PORTB &= ~(1<<2); // desliga led vermelho
			PORTB |= (1<<3); // liga led verde
			if(cont > 9){
				cont = 0;
				PORTB |= (1<<1); // liga buzzer
				_delay_ms(2000); // espera 2s
				PORTB&= ~(1<<1); // desliga buzzer
			}
			PORTD = cont; // incrementa display
		}
	}
}
