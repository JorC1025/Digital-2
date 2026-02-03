/*
 * Digital2Lab2.c
 *
 * Created: 25/1/2026 12:45:50
 * Author : Jorge Cruz
 */ 

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include "LCD/LCD.h"
#include "ADC1/ADC1.h"
#include "UART/UART.h"

volatile uint8_t valor_adc = 0;
float voltaje = 0;
char buffer[10];  

volatile uint8_t valor_adc1 = 0;
float voltaje1 = 0;
char buffer1[10];

volatile uint8_t contador = 0;
char buf_cont[10];

void setup(){
	
	cli();
	
	DDRC &= ~(1 << DDC0);
	DDRC &= ~(1 << DDC1);
	DDRC &= ~(1 << DDC2);
	PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2);
	
	initADC();
	initUAT();
	sei();
	
}

int main(void)
{
	setup();
	
	initLCD8bits(); //Se inicia la LCD en modo 8 bits
	LCD_Set_Cursor(1,1); //Se da la posición para los títulos en la primera fila
	LCD_Write_String("S1:");

	LCD_Set_Cursor(7,1);
	LCD_Write_String("S2:");
	
	LCD_Set_Cursor(14,1);
	LCD_Write_String("S3:");
		
  
    while (1) 
    {
		
		_delay_ms(100);
		voltaje1 = ((float)valor_adc1 * 5.0f) / 255.0f;
		LCD_Set_Cursor(1,2);
		LCD_Write_String("   ");
		dtostrf(voltaje1, 4, 2, buffer1);
		LCD_Set_Cursor(1,2);
		LCD_Write_String(buffer1);
		LCD_Set_Cursor(5,2);
		LCD_Write_Char('V');
		
		_delay_ms(100);
		voltaje = ((float)valor_adc * 5.0f) / 255.0f;
		LCD_Set_Cursor(1,2);
		LCD_Write_String("   ");
		dtostrf(voltaje, 4, 2, buffer);
		LCD_Set_Cursor(7,2);
		LCD_Write_String(buffer);
		LCD_Set_Cursor(11,2);
		LCD_Write_Char('V');
		
		
		ADCSRA |= (1 << ADSC);		
		//Función Contador Serial
		LCD_Set_Cursor(13,2);
		LCD_Write_String("     ");
		LCD_Set_Cursor(13,2);
		itoa(contador, buf_cont, 10);
		LCD_Write_String(buf_cont);
		
		writeString("S1: ");
		writeString(buffer1);
		writeString("V");
		writeString("\r\n");
		
		writeString("S2: ");
		writeString(buffer);
		writeString("V");
		writeString("\r\n");
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
	
	}
	initADC();	
}

ISR (USART_RX_vect){
	char dato_recibido = UDR0;
	
	if (dato_recibido == '+')
	{
		contador++;
		
	} else if (dato_recibido == '-'){
		
		contador--;
		
	}	


}