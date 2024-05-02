/*
 * USART.c
 *
 * Created: 26/04/2024 19:23:01
 * Author : 20232ewbj0262
 */ 
#define CPU_F 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"
#include "def_principais.h"

unsigned char digitos[tam_vetor]; //pertence a USART.h
const char msg[] PROGMEM = " Cronometro: ";
int ADC_valor;
int estouro;
int segundos;
int minutos;
int horas;

int main(void){
	cli(); // desabilita a interrupção global
	TCNT0 = 0; //registrador que armazena o valaor atual da contagem
	TCCR0B = (1<<CS02); // PRESCALE DE 1:256
	TIMSK0 = (1<<TOIE0); //Habilita a interrupção por estouro
	sei(); //Habilita as interrup??es gerais
	USART_Inic(MYUBRR);
	ADMUX = (1<<REFS0) | (1<<MUX1);
	//ADCSRA = (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
	ADCSRA = 0b11101111;
	ADCSRB = 0b00000000;
	
	DDRC = 0b00000000;
	PORTC = 0b11111011;
	set_bit(DIDR0,2); //registrador para controle de entrada ADC
	
    while (1) {}
}

ISR(ADC_vect){
	ADC_valor = ADC;
}

void escreveCronometro(int horas, int minutos, int segundos){
		escreve_USART_Flash(msg);
		ident_num(horas,digitos);
		USART_Transmite(digitos[1]);
		USART_Transmite(digitos[0]);
		USART_Transmite(':');
		ident_num(minutos,digitos);
		USART_Transmite(digitos[1]);
		USART_Transmite(digitos[0]);
		USART_Transmite(':');
		ident_num(segundos,digitos);
		USART_Transmite(digitos[1]);
		USART_Transmite(digitos[0]);
		USART_Transmite('\n');
}

ISR(TIMER0_OVF_vect){
	estouro++;
	if(estouro==248){
		PORTD^=(1<<0);
		estouro=0;
		segundos++;
		escreveCronometro(horas,minutos,segundos);
	}
	if(segundos==60){
		segundos = 0;
		minutos++;
		escreveCronometro(horas,minutos,segundos);
	}
	if(minutos == 60){
		minutos = 0;
		horas++;
		escreveCronometro(horas,minutos,segundos);
	}
	
	if(horas == 24){
		horas = 0;
		escreveCronometro(horas,minutos,segundos);
	}
}