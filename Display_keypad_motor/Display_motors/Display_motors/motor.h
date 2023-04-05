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

// Encoder Motor
/*Interrupt setup function*/
void interrupt_setup(){
    DDRB = 0xFF; // Make PORTB as output Port
    DDRB &= ~(1<<PB2); // Make INT2 pin as Input
    DDRB |= (1<<PB3); // Make OC0 pin as Output
    DDRD &= ~(1<<PD2); // Make INT0 pin as Input
    DDRD &= ~(1<<PD3); // Make INT0 pin as Input
    GICR = (1<<INT2)|(1<<INT1)|(1<<INT0); // Enable INT0, INT2
    MCUCR = (1<<ISC00)|(1<<ISC10); // Trigger INT0 on Logic change trigger
    MCUCSR = (1<<ISC2);// Trigger INT2 on Rising Edge triggered
    sei(); // Enable Global Interrupt */
}

/* Interrupt ISR functions */
ISR(INT0_vect){
    cur_encode = PIND & ((1<<PD2)|(1<<PD3));
    cur_encode = (cur_encode>>2);
    // From the encoder value chart, when Channel A changes logic states we look
    // at the value of the interrupt pins. If they are either 0b 11 or 0b 00,
    // the motor is moving CW and we decrease the count
    if(cur_encode == 0x03 || cur_encode == 0x00){
    count-=1;
    }
    // If they are either 0b 10 or 0b 01, the motor is moving CCW and we increase the count
    else if(cur_encode == 0x02 || cur_encode == 0x01){
    count+=1 ;
    }
}

ISR(INT1_vect){
    cur_encode = PIND & ((1<<PD2)|(1<<PD3)); // Obtain the reading from the PIND2 and PIND3
    cur_encode = (cur_encode>>2);
    // From the encoder value chart, when Channel B changes logic states we look
    // at the value of the interrupt pins. If they are either 0b 01 or 0b 10,
    // the motor is moving CW and we decrease the count
    if(cur_encode == 0x01 || cur_encode == 0x02){
    count-=1;
    }
    // If they are either 0b 11 or 0b 00, the motor is moving CCW and we increase the count
    else if(cur_encode == 0x03 || cur_encode == 0x00){
    count+=1;
    }
}

/*Timer setup function*/
void timer_setup(){
    TIMSK |= (1<<TOIE1); // Activate the timer overflow interrupt
    TCCR1B = (1<<CS11)|(1<<CS10); // Set the timer prescalar to 64
    TCNT1 = 3036; // Load the countdown value for 500ms
}
/*Timer overflow ISR*/
ISR(TIMER1_OVF_vect){
    cur_count = count;
    RPM = (cur_count-prev_count)*120/(96); // Calculate the RPMs
    prev_count = cur_count;
    TCNT1 = 3036;
}

#endif /* motor_H_ */