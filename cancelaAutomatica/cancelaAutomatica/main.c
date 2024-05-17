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
#define PERIODO_SUBIDA 7
#define PERIODO_DESCIDA 23
int carros = 0;
int sobe = 0;
int desce = 0;
volatile int cont = 0;
volatile uint8_t incremento = 0;

void updateLCD() {
	// Salva o novo valor na EEPROM
	eeprom_write_byte((uint8_t*)ADDR_VAR, carros);
	
	// Atualiza o LCD
	lcd_goto_xy(0,0);
	lcd_write_word("Estacionamento: ");
	lcd_goto_xy(1,0);
	lcd_write_integer(carros);
	if(carros <= 9){
		lcd_goto_xy(1,2);
		lcd_write_word("carros");
	}else if(carros <= 99){
		lcd_goto_xy(1,3);
		lcd_write_word("carros");
	}else{
		lcd_goto_xy(1,4);
		lcd_write_word("carros");
	}
}

int main(void){
	cli();
	DDRB |= (1<<3); // Configura o pino PB3 (OC2A) como sa�da
	DDRB |= (1<<0); // led Verde
	DDRB |= (1<<1); // led Amarelo
	DDRB |= (1<<2); // led vermelho
	
	EICRA = 0b00001111; // Habilita interrup��o por borda de subida INT0 e INT1
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
	
	TCNT2 = 0; //registrador que armazena o valaor atual da contagem
	
	TIMSK2 = (1<<TOIE2); //Habilita a interrup��o por estouro
	
	// Carrega o valor armazenado na EEPROM na vari�vel
	carros = eeprom_read_byte((uint8_t*)ADDR_VAR);
	
	lcd_init(); //Inicia o LCD
	updateLCD(); // atualiza lcd
	
	OCR2A = PERIODO_DESCIDA; // Abaixa a cancela (servo motor)
	PORTB |= (1<<2); // liga semaforo vermelho

	while(1){
		// Configura o modo de sono como SLEEP_MODE_DOWN
		//set_sleep_mode(SLEEP_MODE_STANDBY);
		//Habilita o modo de sono
		//sleep_enable();
		// dorme ate que uma interrupcao ocorra
		//sleep_cpu();
	}
}

ISR(TIMER2_OVF_vect) {
	cont++;
	if (cont == 2) {
		cont = 0;
		if (sobe) {
			if (OCR2A > PERIODO_SUBIDA) {
				OCR2A--;
				} else {
				PORTB &= ~(1<<2);
				PORTB |= (1<<0);
				sobe = 0;
			}
			} else if (desce) {
			if (OCR2A < PERIODO_DESCIDA) {
				if (OCR2A == 12) {
					PORTB &= ~(1<<0);
					PORTB |= (1<<1);
				}
				OCR2A++;
				} else {
				PORTB &= ~(1<<1);
				PORTB |= (1<<2);
				desce = 0;
			}
		}
	}
}
ISR(INT0_vect) {
	if(incremento){
		carros++;
		incremento = 0;
	}
	sobe = 0;
	desce = 1;
	updateLCD();
}

ISR(INT1_vect) {
	incremento = 1;
	desce = 0;
	sobe = 1;
}
