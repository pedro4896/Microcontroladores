/*
 * USART.c
 *
 * Created: 26/04/2024 19:23:01
 * Author : 20232ewbj0262
 */ 
#include <avr/interrupt.h>
#include "USART.h"
#include "def_principais.h"

unsigned char digitos[tam_vetor]; //pertence a USART.h
const char msg[] PROGMEM = " Leitura analógica: ";

//float voltage();
int ADC_valor;

int main(void){
	sei(); //Habilita as interrupções gerais
	USART_Inic(MYUBRR);
	ADMUX = (1<<REFS0) | (1<<MUX1);
	//ADCSRA = (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);
	ADCSRA = 0b11101111;
	ADCSRB = 0b00000000;
	
	DDRC = 0b00000000;
	PORTC = 0b11111011;
	set_bit(DIDR0,2); //registrador para controle de entrada ADC
	
    while (1) {
		escreve_USART_Flash(msg);
		//ident_num((float)voltage(),digitos);
		ident_num(ADC_valor,digitos);
		
		USART_Transmite(digitos[3]);
		USART_Transmite(digitos[2]);
		USART_Transmite(digitos[1]);
		USART_Transmite(digitos[0]);
		USART_Transmite('\n');
		_delay_ms(1000);
    }
}

ISR(ADC_vect){
	ADC_valor = ADC;
}

/*float voltage(){
	set_bit(ADCSRA,ADSC); //inicia a conversão analógica
	while(tst_bit(ADCSRA,ADSC)); // espera a conversão ser finalizada
	return(ADC);
}*/

