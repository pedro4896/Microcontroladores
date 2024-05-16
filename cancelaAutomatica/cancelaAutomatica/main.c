/*
 * main.c
 *
 * Author : Pedro Victor
 */ 

#define F_CPU 16000000
#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>

#define ADDR_VAR 0
volatile uint8_t debounce_flag = 0; // Flag para controle do debounce
int carros = 0;

int main(void){
	cli();
	DDRB |= (1<<3); // Configura o pino PB3 (OC2A) como sa�da
	DDRB |= (1<<4);
	DDRB |= (1<<5);
	PORTB &= ~(1<<4);
	PORTB &= ~(1<<5);
	
	EICRA = 0b00001111; // Habilita interrup��o por borda de subida INT0
	sei();
	EIMSK = 0b00000011;
	
	//PWM R�pido
	TCCR2B &= ~(1<<WGM22);
	TCCR2A |= (1<<WGM21) | (1<<WGM20);
		
	//Prescaler 1024
	TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);
		
	//evento no pino OC2A
	TCCR2A |= (1<<COM2A1);
	TCCR2A &= ~(1<<COM2A0);
	
	// Carrega o valor armazenado na EEPROM na vari�vel
	carros = eeprom_read_byte((uint8_t*)ADDR_VAR);
	
	//Inicia o LCD
	lcd_init();
	lcd_goto_xy(0,0);
	lcd_write_word("Estacionamento: ");
	lcd_goto_xy(1,0);
	lcd_write_integer(carros);
	
	OCR2A = 23; // Abaixa a cancela (servo motor)
	
	while(1){
		while(!debounce_flag);
		debounce_flag = 0; // Reseta a flag de debounce
		// Configura o modo de sono como SLEEP_MODE_DOWN
		set_sleep_mode(SLEEP_MODE_STANDBY);
		//Habilita o modo de sono
		sleep_enable();
		_delay_ms(100);
		// dorme ate que uma interrupcao ocorra
		sleep_cpu();
	}
}

ISR(INT0_vect){
	    if (!debounce_flag) { // Verifica se o debounce já não foi ativado
		    debounce_flag = 1; // Ativa a flag de debounce
			OCR2A = 23; // Abaixa a cancela (servo motor)
			carros++; //incrementa os carros
			
			// atualiza LCD
			lcd_goto_xy(0,0);
			lcd_write_word("Estacionamento: ");
			lcd_goto_xy(1,0);
			lcd_write_integer(carros);
			
			// Salva o novo valor na EEPROM
			eeprom_write_byte((uint8_t*)ADDR_VAR, carros);
		}
}

ISR(INT1_vect){
	    if (!debounce_flag) { // Verifica se o debounce já não foi ativado
		    debounce_flag = 1; // Ativa a flag de debounce
			OCR2A = 7; // levanta a cancela (servo motor)
			PORTB |= (1<<5);
		}
}
