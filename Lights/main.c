/*
 * lights.c
 *
 * Created: 05/12/2022 08:38:02
 * Author : Austin
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB = 0x0F;
	DDRC = 0x00;
	//Pulling up the button
	PORTC = 1<<PC0;
    while (1) 
    {
		PORTB |= 1<<PB1;
		PORTB |= 1<<PB2;
		if (PINC != 0x01){
			PORTB = 0;
			PORTB |= 1<<PB0;
			PORTB |= 1<<PB3;
			_delay_ms(60000);
			PORTB = 0;
			PORTB |= 1<<PB2;
		}
    }
}

