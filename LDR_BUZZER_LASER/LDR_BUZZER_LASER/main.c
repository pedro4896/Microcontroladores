/*
 * LDR_BUZZER_LASER.c
 *
 * Created: 12/04/2024 16:23:51
 * Author : Pedro Victor
 */ 

#define F_CPU 16000000 // Frequência do cristal oscilador externo

#include <avr/io.h>
#include <util/delay.h> //Só funcionar se definir a frequência do cristal

int main(void){
	DDRD = 0b01111111;
	PORTD = 0;
    while (1) { //loop infinito
		if(PIND&(1 << 7)){ // verifica estado do ldr (ausência de luz retorna 1 / presença de luz retorna 0)
			PORTD &= ~(1 << 6); //desliga led verde
			PORTD |= (1 << 5); //liga led vermelho
		} else{
			PORTD |= (1 << 6); //liga led verde
			PORTD &= ~(1 << 5); //desliga led vermelho
		}
    }
}