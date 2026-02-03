/*
 * UART.h
 *
 * Created: 30/1/2026 00:15:05
 *  Author: jorge
 */ 


#ifndef UART_H_
#define UART_H_
#define F_CPU 16000000

#include <util/delay.h>
#include <avr/io.h>
void initUAT();
void writeChar(char caracter);
void writeString(char* texto);



#endif /* UART_H_ */