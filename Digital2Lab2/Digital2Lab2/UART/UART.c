/*
 * UART.c
 *
 * Created: 30/1/2026 00:15:18
 *  Author: jorge
 */ 

#include "UART.h"


void initUAT(){
	//Se usa PD0 y PD1
	//Mirar el pinout
	DDRD |= (1<<DDD1);
	DDRD &=~ (1<<DDD0);
	
	//Configurar UCS0A
	UCSR0A = (1<<U2X0);
	
	//Se configura baud rate
	UBRR0 = 207; //9600 @ 16MHz
	
	UCSR0B = (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);
	
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	
	
		
}

void writeChar(char caracter){

	
	while ((UCSR0A & (1<<UDRE0))==0);
	UDR0 = caracter;
	
}

void writeString(char* texto){ //Funcion de escribir string
	
	for (uint8_t i =0; *(texto+i)!='\0'; i++)
	{
		writeChar(*(texto+i));
	}
	
}