/*
 * pwmRegistradores.c
 *
 * Created: 03/05/2024 19:28:38
 * Author : 20232ewbj0262
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char i = 0;
int ms = 0;
int rotina = 0;
int main(void){
	cli();
	
	DDRD = (1<<6) | (1<<5);
	TCCR0A = (1<<COM0A1) | (1<<COM0B1) | (1<<WGM01) | (1<<WGM00); // PWM rápido com incremento com estouro em 255
	TCCR0B = (1<<CS01) | (1<<CS00); //PRESCALER 1:64
	
	TCCR2A = 0;
	TCCR2B = (1<<CS22); // PRESCALER 1:64 no TIMER 2
	TIMSK2 = (1<<TOIE2); // habilita a interrupção por estouro
	TCNT2 = 5;
	
	sei();
    while (1) {}
}

ISR(TIMER2_OVF_vect){
	ms++;
	TCNT2 = 5;
	if(rotina == 0){
		if(ms == 10){
			ms = 0;
			OCR0A++;
			if(OCR0A == 255){
				rotina = 1;
			}
		}
	} else{
		if(ms == 10){
			ms = 0;
			OCR0A--;
			if(OCR0A == 0){
				rotina = 0;
			}
		}
	}

}

