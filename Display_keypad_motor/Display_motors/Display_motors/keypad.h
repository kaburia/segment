#ifndef keypad_H_
#define keypad_H_

/*Useful pin and port definitions*/
#include <avr/eeprom.h>
#include <util/delay.h>
#include "LCD.h"
#include "ADC.h"
#include <string.h>
#include <math.h>
#include "motor.h"
#include <stdlib.h>

// initialize
#define F_CPU 8000000UL


/*Keypad configuration*/
uint8_t read_keypad(void)
{
	// Wait for the data to be available
	while (!(PIND & (1 << PD2)));

	// Read the data from the keypad
	int value = PINB;
	int data = 255; // initialize to a default value
	switch (value)
	{
		case 0:
		data = 7;
		LCD_String("*");
		break;
		case 1:
		data = 8;
		LCD_String("*");
		break;
		case 2:
		data = 9;
		LCD_String("*");
		break;
		case 3:
		LCD_String("/");
		break;
		case 4:
		data = 4;
		LCD_String("*");
		break;
		case 5:
		data = 5;
		LCD_String("*");
		break;
		case 6:
		data = 6;
		LCD_String("*");
		break;
		case 7:
		//LCD_String("*");
		data = 200; // A generic value to indicate that the key is *
		break;
		case 8:
		data = 1;
		// LCD_String("*");
		DC_Motor();
		break;
		case 9:
		data = 2;
		LCD_String("*");
		// encoder
		encoder();
		break;
		case 10:
		data = 3;
		LCD_String("*");
		break;
		case 11:
		LCD_String("-");
		break;

		case 12: // ON/C
		LCD_Clear();
		LCD_String("THE MATRIX!!");
		// reset the password if safe is open
		break;

		case 13:
		data = 0;
		LCD_String("*");
		break;
		case 14:
		
		break;
		case 15:
		LCD_String("+");
		break;
		
	}

	// Debounce delay
	_delay_ms(500);

	return data;
}


#endif /* keypad_H_ */
