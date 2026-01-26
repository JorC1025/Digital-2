/*
 * Digital2PLab1.c
 *
 * Created: 19/1/2026 22:42:41
 * Author : Jorge Cruz
 */ 

#define F_CPU 16000000 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Display7seg/Display7seg.h"


volatile uint8_t p1 = 0;
volatile uint8_t p2 = 0;
volatile uint8_t start_seq = 0;
volatile uint8_t start_game = 0;
volatile uint8_t punt_display = 0;
volatile uint8_t pos = 0;
volatile uint8_t temp = 0;



void setup(){
	cli();


	DDRD = 0xFF; //Puerto D se configura como salidas
	
	DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (1<<DDB3); //Los 4 bits bajos del puerto B se configuran como salidas
	DDRB &= ~(1<<DDB5); //El bit 5 se configura como entrada
	PORTB |= (1 << PORTB5); //Pullups internos activados
	
	
	DDRC |= (1<<DDC0) | (1<<DDC1) | (1<<DDC2) | (1<<DDC3); //Los 4 bits bajos del puerto C se configuran como salidas
	DDRC &= ~(1<<DDC4); //El bit 4 se configura como entrada
	DDRC &= ~(1<<DDC5); //El bit 5 se configura como entrada
	PORTC |= (1 << PORTC4) | (1 << PORTC5); //Pullups internos activados
	
	UCSR0B = 0x00; //Apagar leds del Atmega
	
	PCICR |= (1 << PCIE0); //Se habilitan interrupciones en el puerto B
	PCMSK0 |= (1 << PCINT5); //Se habilitan interrupciones para el pin 5 del puerto B.
		
	PCICR |= (1 << PCIE1); //Se habilitan interrupciones en el puerto C
	PCMSK1 |= (1 << PCINT12) | (1 << PCINT13); //Se habilitan interrupciones para los pines 4 y 5 del puerto C.
	
	PORTB = 0;
	PORTC = 0;
	
	p1 = 0;
	p2 = 0;
		
	// Leer los puertos para limpiar estado inicial
	uint8_t tempB = PINB;
	uint8_t tempC = PINC;

	//Sección del timer
	CLKPR = (1<<CLKPCE) ; // Cambios en el preescaler
	CLKPR = (1<<CLKPS2); //1MHz
	
	TCCR1A = 0;
	TCCR1B = 0;
	
	TCCR1B |= (1 << WGM12);
	
	OCR1A = 15624;
	TIMSK1 |= (1 << OCIE1A);

	//Empezar el timer
	TCNT1 = 0;
	TIFR1 |= (1 << OCF1A);
	TCCR1B |= (1 << CS11) | (1 << CS10);	
	
	sei();
	
	
}


int main(void)
{

	setup();	

    while (1) 
    {

	
    }
}



ISR (PCINT1_vect){
	if (start_game == 1)
	{
		if (!(PINC & (1 << PINC4)))
		{
				PORTB = (PORTB & 0xF0) | p1;
				
				p1++;

			if (p1 == 4)
			{
				start_game = 0;
				start_seq = 0;
				p1 = 0;
				p2 = 0;
				PORTB = 0x0F;
				PORTC = 0x00;
				PORTD = 0x30;
			}
			
		}
		
		if (!(PINC & (1 << PINC5)))
		{
				PORTC = (PORTC & 0xF0) | p2;
				p2++;
						
			if (p2 == 4)
			{
				start_game = 0;
				start_seq = 0;
				p1 = 0;
				p2 = 0;
				PORTB = 0x00;
				PORTC = 0x0F;
				PORTD = 0x6D;
			}
		}
	}
}


ISR (PCINT0_vect){
	
	
	
		if (!(PINB & (1 << PINB5)))
		{
			start_seq = 1;

			
		} 
	
}

ISR(TIMER1_COMPA_vect){

if (start_seq == 1)
{
		display(pos);
		pos++;
		if (pos == 6)
		{
			pos = 0;
			start_game = 1;
			start_seq = 0;
			p1 = 0;
			p2 = 0;
			PORTB = 0;
			PORTC = 0;
		}
		
}
		


} 
