/*
 * introducao.c
 *
 * Created: 11/04/2024 19:28:40
 * Author : Pedro Victor
 */ 

#define	F_CPU 16000000 // frequência do cristal oscilador externo

#include <avr/io.h>
#include <util/delay.h> //so funciona se definir a frenquencia do cristal

#define setbit(port,bit) port |= (1<<bit) //macro SETBIT
#define clearbit(port,bit) port &= ~(1<<bit) //macro CLEARBIT

int main(void){
	DDRD = 0b00001111;
	PORTD = 0;
	int c = 0;
    while (1) { //loop infinito
		/*PORTD = PORTD |(1 << 0); //SET BIT PD0
		// PORTD |= (1<<0);
		PORTD &= ~(1<<0); //CLEAR BIT PD0*/
		
		if((PIND&(1 << 7))){
			c++; 
			while((PIND&(1 << 7))){}
		}else{
			PORTD &= ~(1 << 0);
		}
		
		if(c==1){
			PORTD |= (1 << 0);
		}
		if(c==2){
			PORTD |= (1 << 1);
		}
		if(c==3){
			PORTD &= ~(1<<0);
			PORTD &= ~(1<<1);
			c = 0;
		}
    }
	_delay_ms(200);
}

