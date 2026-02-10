/*
 * Digital2Lab3.c
 *
 * Created: 2/2/2026 22:42:49
 * Author : Jorge Cruz - 23502
 * Erick Perez - 23001
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SPI/SPI.h"
#include "ADC1/ADC1.h"
uint8_t valorSPI = 0;

volatile uint8_t valor_adc = 0;
float voltaje = 0;
char buffer[10];

volatile uint8_t valor_adc1 = 0;
float voltaje1 = 0;
char buffer1[10];

uint8_t contador = 0;

void refreshPort(uint8_t valor);


void setup(){
		cli();
		
		DDRC &= ~(1 << DDC0);
		DDRC &= ~(1 << DDC1);
		DDRC &= ~(1 << DDC2);
		PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2);
		DDRD |= (1 << DDD0) | (1 << DDD1) |(1 << DDD2) |(1 << DDD3) |(1 << DDD4) |(1 << DDD5) |(1 << DDD6) |(1 << DDD7);
		initADC();
		sei();
		
	
	
}



int main(void)
{
    /* Replace with your application code */
	setup();
	spiInit(SPI_SLAVE_SS, SPI_DATA_ORDER_MSB, SPI_CLOCK_IDLE_LOW, SPI_CLOCK_FIRST_EDGE);
	initADC();
	SPCR |= (1<<SPIE);
    while (1) 
    {
		/*
		_delay_ms(100);
		
		spiWrite(valor_adc);
		_delay_ms(100);
		spiWrite(valor_adc1);
		*/
		ADCSRA |= (1<<ADSC);
		/*
		contador = spiRead();
		PORTD = contador;
		*/
    }
}

ISR(ADC_vect){
			
			switch(canal){
				case 0:
				valor_adc = ADCH;
				canal = 1;
				break;
				case 1:
				valor_adc1 = ADCH;
				canal = 0;
				break;
				initADC();
			}
				
	
}

ISR(SPI_STC_vect){
	uint8_t spiValor = SPDR;
	if (spiValor == 'c')
	{
		SPDR = valor_adc;
	} else if (spiValor == 'd')
	{
		SPDR = valor_adc1;
	}
  else
  {
	  PORTD = spiValor;
	  SPDR = 0x00; // No enviamos nada útil de vuelta
  }
	
}