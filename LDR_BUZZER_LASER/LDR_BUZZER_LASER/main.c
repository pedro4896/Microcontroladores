/*
 * LDR_BUZZER_LASER.c
 *
 * Created: 12/04/2024 16:23:51
 * Author : Pedro Victor
 */ 

#define F_CPU 16000000 // Frequ�ncia do cristal oscilador externo

#include <avr/io.h>
#include <util/delay.h> //S� funcionar se definir a frequ�ncia do cristal

int main(void){
	DDRD = 0b01111111;
	PORTD = 0;
    while (1) { //loop infinito
		if(PIND&(1 << 7)){ // verifica estado do ldr (aus�ncia de luz retorna 1 / presen�a de luz retorna 0)
			PORTD &= ~(1 << 6); //desliga led verde
			PORTD |= (1 << 5); //liga led vermelho
		} else{
			PORTD |= (1 << 6); //liga led verde
			PORTD &= ~(1 << 5); //desliga led vermelho
		}
    }
}