/*
 * SPI.h
 *
 * Created: 2/2/2026 22:49:45
 *  Author: Jorge Cruz - 23502
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <stdint.h>

typedef enum
{
	SPI_MASTER_OSC_DIV2   = 0b01010000,
	SPI_MASTER_OSC_DIV4   = 0b01010001,
	SPI_MASTER_OSC_DIV8   = 0b01010010,
	SPI_MASTER_OSC_DIV16  = 0b01010011,
	SPI_MASTER_OSC_DIV32  = 0b01010100,
	SPI_MASTER_OSC_DIV64  = 0b01010101,
	SPI_MASTER_OSC_DIV128 = 0b01010110,
	SPI_SLAVE_SS          = 0b01000000
	
	}Spi_Type;
	
typedef enum
{
	SPI_OSC_DIV2   = 0b01010000,
	SPI_OSC_DIV4   = 0b01010001,
	SPI_OSC_DIV8   = 0b01010010,
	SPI_OSC_DIV16  = 0b01010011,
	SPI_OSC_DIV32  = 0b01010100,
	SPI_OSC_DIV64  = 0b01010101,
	SPI_OSC_DIV128 = 0b01010110,

	
}Spi_Osc_Div;	
	
typedef enum {
	
	SPI_DATA_ORDER_MSB = 0b00000000,
	SPI_DATA_ORDER_LSB = 0b00100000
		
	}Spi_Data_Order;	
	
typedef enum {
	
	SPI_CLOCK_IDLE_HIGH = 0b00001000,
	SPI_CLOCK_IDLE_LOW  = 0b00000000,
	
	}Spi_Clock_Polarity;
	
typedef enum{
	
	SPI_CLOCK_FIRST_EDGE = 0b00000000,
	SPI_CLOCK_LAST_EDGE  = 0b00000100
	
	}Spi_Clock_Phase;	
	
void spiInit(Spi_Type sType, Spi_Data_Order sDataOrder, Spi_Clock_Polarity sClockPolarity, Spi_Clock_Phase sClockPhase);
void spiWrite(uint8_t dat);
unsigned spiDataReady();
uint8_t spiRead(void);

#endif /* SPI_H_ */