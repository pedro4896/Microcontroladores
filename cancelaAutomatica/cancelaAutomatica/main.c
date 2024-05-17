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

#define ADDR_VAR 0 // Endereco EEPROM
/* -------  Servo Motor ---------------- */
#define PERIODO_SUBIDA 7
#define PERIODO_DESCIDA 23
/* ------- Variaveis Auxiliares --------------- */
int carros = 0;
int sobe = 0;
int desce = 0;
volatile int estouro = 0;
volatile uint8_t incremento = 0;

/* -----Funcao de atualizacao do LCD ----- */
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
	cli(); // desativa as interrupcoes 
	// ------ Configuracao de registradores --------
	DDRB |= (1<<3); // pino PWM-OCR2A (servo motor)
	DDRB |= (1<<0); // led Verde
	DDRB |= (1<<1); // led Amarelo
	DDRB |= (1<<2); // led vermelho
	DDRB |= (1<<5); // led vermelho
	
	
	//------ Configuracao de interrupcao externa --------
	EICRA = 0b00001111; // configura interrup��o por borda de subida INT0 e INT1
	sei();
	EIMSK = 0b00000011; // habilita as interrupcoes no INT0 e INT1
	
	//------ Configuracao Timer2/PWM --------
	//PWM Rapido
	TCCR2B &= ~(1<<WGM22);
	TCCR2A |= (1<<WGM21) | (1<<WGM20);
	//Prescaler 1024
	TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);
	//evento no pino OC2A na igualdade de comparacao
	TCCR2A |= (1<<COM2A1);
	TCCR2A &= ~(1<<COM2A0);
	//registrador que armazena o valaor atual da estouroagem
	TCNT2 = 0;
	//Habilita a interrupcao por estouro
	TIMSK2 = (1<<TOIE2); 
	
	//--- Carrega o valor armazenado na EEPROM na vari�vel ------
	carros = eeprom_read_byte((uint8_t*)ADDR_VAR);
	
	//------ Configuracao LCD --------
	lcd_init(); //Inicia o LCD
	updateLCD(); // atualiza lcd
	
	//------ Configuracoes iniciais do sistema --------
	OCR2A = PERIODO_DESCIDA; // Abaixa a cancela (servo motor)
	PORTB |= (1<<2); // liga semaforo vermelho

	while(1){
		// Configura o modo de sono como Extand Standby
		set_sleep_mode(SLEEP_MODE_EXT_STANDBY);
		//Habilita o modo de sono
		sleep_enable();
		// dorme ate que uma interrupcao ocorra
		sleep_cpu();
	}
}

// Rotina do Timer2
ISR(TIMER2_OVF_vect) {
	estouro++; // cada estouro do timer = 16ms
	if (estouro == 2) { // 32ms
		estouro = 0; // zera o estouro
		if (sobe) { // rotina para subir a cancela
			if (OCR2A > PERIODO_SUBIDA) { 
				OCR2A--; //decrementa PWM
				} else {
				PORTB &= ~(1<<2); // desliga led vermelho
				PORTB |= (1<<0); // liga led verde
				sobe = 0; // desliga a rotina para subir a cancela
			}
			} else if (desce) { // rotina para descer a cancela
			if (OCR2A < PERIODO_DESCIDA) {
				if (OCR2A == 12) {
					PORTB &= ~(1<<0); // desliga led verde
					PORTB |= (1<<1); // liga led amarelo
				}
				OCR2A++; //incrementa PWM
				} else {
				PORTB &= ~(1<<1); // desliga led amarelo
				PORTB |= (1<<2); // liga led vermelho
				desce = 0; // desliga a rotina para descer a cancela
			}
		}
	}
}

// Rotina interrupcao no INT0
ISR(INT0_vect) {
	if(incremento){ 
		carros++; // incrementa a quantida de carros
		incremento = 0; 
	}
	sobe = 0;
	desce = 1;
	updateLCD();
}

// Rotina interrupcao no INT1
ISR(INT1_vect) {
	incremento = 1;
	desce = 0;
	sobe = 1;
}
