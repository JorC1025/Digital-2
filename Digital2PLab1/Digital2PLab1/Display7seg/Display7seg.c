/*
 * CFile1.c
 *
 * Created: 20/1/2026 17:13:35
 *  Author: jorge
 */ 


#include "Display7seg.h"
int numeros[] = {0x5B, 0x33, 0x79, 0x6D, 0x30, 0xFE};
void display(uint8_t pos){
	
	PORTD = numeros[pos];
	
	
}
