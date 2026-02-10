/*
 * ADC1.c
 *
 * Created: 27/1/2026 17:09:40
 *  Author: jorge
 */ 

#include "ADC1.h"

volatile uint8_t canal = 0;

void initADC(void){
	
	switch(canal){
		
		case 0:
		ADMUX = 0;
		ADMUX |= (1 << REFS0)  | (1 << ADLAR)| (1<< MUX1);
		
		ADCSRA = 0;
		ADCSRA |= (1 << ADPS1) |(1<<ADPS0) | (1<< ADEN) | (1<<ADIE);
		
		ADCSRA |= (1 << ADSC);
		break;
		
		case 1:
		
		ADMUX = 0;
		ADMUX |= (1 << REFS0)  | (1 << ADLAR) | (1<< MUX0);
		
		ADCSRA = 0;
		ADCSRA |= (1 << ADPS1) |(1<<ADPS0) | (1<< ADEN) | (1<<ADIE);
		
		ADCSRA |= (1 << ADSC);
		break;
						
		
		
	}	
}
