/*
 * GccApplication2.c
 *
 * Created: 30-03-2021 10.07.11 PM
 * Author : mintu
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRC = 0xFF;
	
	while(1)
	{
		PORTC = 0xFF;
		_delay_ms(1000);
		PORTC = 0x00;
		_delay_ms(1000);
	}
}

