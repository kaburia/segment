#ifndef motor_H_
#define motor_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "LCD.h"
#include "ADC.h"
#include <string.h>
#include <math.h>
#include "motor.h"
#include <stdlib.h>

void PWM_init(void){
    TCNT0 = 0; /* Set timer0 count zero */
    // Set fast PWM mode with non inverted output clock prescaler 64
    TCCR0 = (1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00)|(1<<CS01);
    // enabler pin connected to pin 4 of port D
    DDRD |= (1<<PD4);
}

// DC Motor
void DC_Motor(void)
{
	LCD_Clear();
	LCD_String("DC Motor");
	LCD_Cmd(0xC0);
	char buffer[10];
		// write one to the motor input
	// PORTB |= (1 << PB5);
	// read the ADC value
	int ADC_value = ADC_Read(0);
	// convert the ADC value to a voltage
	float voltage = (ADC_value * 5.0) / 1024.0;
	// convert the voltage to a duty cycle
	int duty_cycle = (int)(voltage * 255.0 / 5.0);
	// set the duty cycle
	OCR0 = duty_cycle;
	LCD_String("Duty Cycle: ");
	// display the duty cycle on the LCD
	LCD_String(itoa(duty_cycle, buffer, 10));
}

#endif /* motor_H_ */