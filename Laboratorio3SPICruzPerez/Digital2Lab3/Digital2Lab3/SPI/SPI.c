/*
 * SPI.c
 *
 * Created: 2/2/2026 22:50:19
 *  Author: Jorge Cruz - 23502
 */ 
#include "SPI.h"

void spiInit(Spi_Type sType, Spi_Data_Order sDataOrder, Spi_Clock_Polarity sClockPolarity, Spi_Clock_Phase sClockPhase)
{
	if (sType & (1<<MSTR))
	{
		DDRB |= (1<<DDB3) | (1<<DDB5) | (1<<DDB2); //MOSI, SCK, NEGADO_SS
		DDRB &= ~(1<<DDB4);
		SPCR |= (1<<MSTR);
		
		uint8_t temp = sType & 0b00000111;
		switch(temp){
			case 0: //DIV2
				SPCR &= ~((1<<SPR1)|(1<<SPR0));
				SPSR |= (1<<SPI2X);
			break;
			
			case 1: //DIV4
				SPCR &= ~((1<<SPR1)|(1<<SPR0));
				SPSR &= ~(1<<SPI2X);
			break;
			case 2: //DIV8
				SPCR |= (1<<SPR0);
				SPCR &= ~(1<<SPR1);
				SPSR |= (1<<SPI2X);
			break;
			case 3: //DIV16
				SPCR |= (1<<SPR0);
				SPCR &= ~(1<<SPR1);
				SPSR &= ~(1<<SPI2X);
			break;
			case 4: //DIV32
				SPCR &= ~(1<<SPR0);
				SPCR |= (1<<SPR1);
				SPSR |= (1<<SPI2X);
			break;
			case 5: //DIV64
				SPCR &= ~(1<<SPR0); 
				SPCR |= (1<<SPR1);
				SPSR &= ~(1<<SPI2X);
			break;	
			case 6: //DIV128
				SPCR |= (1<<SPR0) | (1<<SPR1);
				SPSR &= ~(1<<SPI2X);
			break;
		}
		
	} else 
	{
		DDRB |= (1<<DDB4); //MISO
		DDRB &= ~((1<<DDB3) | (1<<DDB5) | (1<<DDB2)); //MOSI, SCK, SS	
		SPCR &= ~(1<<MSTR);
	}
SPCR |= (1<<SPE)|sDataOrder|sClockPolarity|sClockPhase;	
}

void spiWrite(uint8_t dat){
	
	SPDR = dat;
	
}

unsigned spiDataReady()
{
	if (SPSR & (1<<SPIF))
	{
		return 1;
	} else 
	{
		return 0;
	}
}

uint8_t spiRead(void)
{
	while (!(SPSR & (1<<SPIF)));
	return(SPDR);
}