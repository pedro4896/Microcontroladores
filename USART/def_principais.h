/*
 * def_principais.h
 *
 * Created: 25/04/2024 11:43:06
 *  Author: Henrique Patriota
 */ 


#ifndef _DEF_PRINCIPAIS_H
#define _DEF_PRINCIPAIS_H
#define F_CPU 16000000UL //define a frequência do microcontrolador - 16MHz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define set_bit(y,bit) (y|=(1<<bit))
#define clr_bit(y,bit) (y&=~(1<<bit))
#define cpl_bit(y,bit) (y^=(1<<bit))
#define tst_bit(y,bit) (y&(1<<bit))
#endif