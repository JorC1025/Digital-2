/*
 * Digital2Lab3Master.c
 *
 * Created: 3/2/2026 17:17:25
 * Author : Jorge Cruz - 23502
 * Erick Perez - 23001
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include "SPI/SPI.h"
#include "UART/UART.h"

char bufferEntrada[5];
uint8_t posBuffer = 0;  // Posición actual en el buffer

float voltaje1 = 0;
float voltaje2 = 0;
char bufferDisp[10];

uint8_t valorSPI = 0;
uint8_t valorSPI2 = 0;

// Contador para no saturar la pantalla con datos
uint16_t contadorTiempo = 0;


void refreshPORT(uint8_t valor);

int main(void)
{
	// LEDs del Maestro: D2-D7 (PORTD) y D8-D9 (PORTB)
	DDRD |= 0xFC;
	DDRB |= 0x03;
	
	DDRC |= (1 << DDC5);
	PORTC |= (1 << PORTC5);

	initUAT();
	spiInit(SPI_MASTER_OSC_DIV128, SPI_DATA_ORDER_MSB, SPI_CLOCK_IDLE_LOW, SPI_CLOCK_FIRST_EDGE);

	while (1)
	{
		if (UART_HayDato())
		{
			char dato = readChar();

			if (dato >= '0' && dato <= '9') {
				if (posBuffer < 3) {
					bufferEntrada[posBuffer++] = dato;
					writeChar(dato);
				}
			}
			else if (dato == 13 || dato == 10) {
				bufferEntrada[posBuffer] = '\0';
				writeString("\r\n");
				
				if (posBuffer > 0) {
					int numero = atoi(bufferEntrada);
					
					if (numero >= 0 && numero <= 255) {
						uint8_t valorFinal = (uint8_t)numero;
						
						refreshPORT(valorFinal);
						
						PORTC &= ~(1 << PORTC5);
						spiWrite(valorFinal);
						spiRead();
						PORTC |= (1 << PORTC5);
					}
					else {
						writeString("Error: Rango 0-255\r\n");
					}
				}
				posBuffer = 0;
			}
		}

		contadorTiempo++;
		
		if (contadorTiempo >= 250)
		{
			contadorTiempo = 0;
			
			if (posBuffer == 0)
			{
				PORTC &= ~(1 << PORTC5);
				spiWrite('c'); spiWrite(0x00);
				valorSPI = spiRead();
				PORTC |= (1 << PORTC5);
				
				_delay_us(100);
				
				PORTC &= ~(1 << PORTC5);
				spiWrite('d'); spiWrite(0x00);
				valorSPI2 = spiRead();
				PORTC |= (1 << PORTC5);
				
				voltaje1 = ((float)valorSPI * 5.0f) / 255.0f;
				dtostrf(voltaje1, 4, 2, bufferDisp);
				writeString("S1: "); writeString(bufferDisp);
				
				voltaje2 = ((float)valorSPI2 * 5.0f) / 255.0f;
				dtostrf(voltaje2, 4, 2, bufferDisp);
				writeString("V | S2: "); writeString(bufferDisp);
				writeString("V\r");
			}
		}

		_delay_ms(1);
	}
}

void refreshPORT(uint8_t valor)
{
	PORTD &= 0b00000011;
	PORTB &= 0b11111100;

	PORTD |= (valor << 2);
	PORTB |= (valor >> 6);
}
