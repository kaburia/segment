/*
 * Keypad And PA0.c
 *
 * Created: 3/3/2023 2:24:48 PM
 * Author : Administrator
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LCD.h"
#include <avr/interrupt.h>
void ADC_Init()
{
	DDRA=0x0;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
	
}

int ADC_Read(char channel)
{
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	
	_delay_us(10);
	AinLow = (int)ADCL;		/* Read lower byte*/
	Ain = (int)ADCH*256;		/* Read higher 2 bits and 
					Multiply with weight */
	Ain = Ain + AinLow;				
	return(Ain);			/* Return digital value*/
}

int main(void)
{
	int value;
	char buffer[5];
	LCD_Init();
	ADC_Init();
	LCD_String("KEYPAD");
	LCD_Cmd(0XC0);
	
    while (1) 
    {
		
		
		value = ADC_Read(0);
		itoa(value,buffer,10);
		
		//LCD_String(buffer);
		//LCD_String(" ");
		if (value==204)
		{
			LCD_String("7");
		}
		else if(value==146)
		{
			LCD_String("8");
		}
		else if(value==79)
		{
			LCD_String("9");
		}
		else if(value==0)
		{
			LCD_String("/");
		}
		else if(value==371)
		{
			LCD_String("4");
		}
		else if(value==335)
		{
			LCD_String("5");
		}
		else if(value==294)
		{
			LCD_String("6");
		}
		else if(value==248)
		{
			LCD_String("*");
		}
		else if(value==481)
		{
			LCD_String("1");
		}
		else if(value==456)
		{
			LCD_String("2");
		}
		else if(value==429)
		{
			LCD_String("3");
		}
		else if(value==399)
		{
			LCD_String("-");
		}
		else if(value==560)
		{
			//LCD_String("ON");
			LCD_Clear();
			LCD_String("ADC VALUE");
			LCD_Cmd(0XC0);
			
		}
		else if(value==542)
		{
			LCD_String("0");
		}
		else if(value==522)
		{
			LCD_String("=");
		}
		else if(value==501)
		{
			LCD_String("+");
		}
		/*else if(value==1023)
		{
			LCD_String("NONE PRESSED");
		}*/
		_delay_ms(500);
    }
}

