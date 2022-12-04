/*
 * interrupts2.c
 *
 * Created: 04/12/2022 06:49:08
 * Author : Austin
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

char check[] = {};
char password[] = {0, 1, 2};
int count = 0;
void password_check();


/*Interrupt Service Routine for INT0*/
ISR(INT0_vect){
	PORTC ^= (1<<PC0); /* Toggle PORTC PC0 */
	_delay_ms(50); /* Software debouncing control delay */
	check[count] = 1;
	count ++;
}
ISR(INT1_vect){
	PORTC ^= (1<<PC1); /* Toggle PORTC PC0 */
	_delay_ms(50); /* Software debouncing control delay */
	check[count] = 2;
	count ++;
}
ISR(INT2_vect){
PORTC ^= (1<<PC2); /* Toggle PORTC PC0 */
_delay_ms(50); /* Software debouncing control delay */
check[count] = 0;
count ++;
}


int main(void)
{
    /* Replace with your application code */
	// Initializing the ports
	DDRB = 0x00;
	DDRC = 0x1F;
	DDRD = 0x03;
	// Pulling up the buttons
	PORTB = 0x4;
	//PORTD = 0xC;
	
	PORTD = PORTD | 1<<PD2;
	PORTD = PORTD | 1<<PD3;
	
	/* Interrupt setup */
	GICR = 1<<INT0; /* Enable INT0*/
	GICR |= 1<<INT2; /* Enable INT2*/
	GICR |= 1<<INT1; /* Enable INT1*/	
	MCUCR |= 1<<ISC01 | 1<<ISC00; /* Trigger INT0 on rising edge */
	MCUCR |= 1<<ISC11 | 1<<ISC10; /* Trigger INT1 on rising edge */
	MCUCSR = 1<<ISC2;
	sei(); /* Enable Global Interrupt */
		
    while (1) 
    {
		password_check();
    }

}

void password_check(){
	if (count == 3){
		count = 0;
		if ((check[0]==password[0])&&(check[1] ==password[1]) &&(check[2] == password[2])){
			PORTD |= 1<<PD0;
			_delay_ms(100);
			PORTD = 0b00000000;
			_delay_ms(100);
			PORTD |= 1<<PD0;
			_delay_ms(100);
			PORTD = 0b00000000;
			_delay_ms(100);
			PORTD |= 1<<PD0;
			_delay_ms(100);
			PORTD = 0b00000000;
			_delay_ms(100);
			PORTC = 0;
		}
		else{
			PORTD |= 1<<PD1;
			_delay_ms(100);
			PORTD = 0b00000000;
			_delay_ms(100);
			PORTD |= 1<<PD1;
			_delay_ms(100);
			PORTD = 0b00000000;
			_delay_ms(100);
			PORTD |= 1<<PD1;
			_delay_ms(100);
			PORTD = 0b00000000;
			_delay_ms(100);
			PORTC=0;
		}
		
	}
	
}