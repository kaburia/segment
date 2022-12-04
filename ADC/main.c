/*
 * ADC.c
 *
 * Created: 04/12/2022 11:07:19
 * Author : Austin
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

int ADC_Read();
int	MapedValue;
int Potval;
int tens, ones;


// Numbers to display in seven segment
char numbers[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
void display_2(int digit);
void display_1(int digit);

void initialize_ADC(){
	ADMUX |= (1<<REFS0); /* Vref: Avcc */
	//set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

int ADC_Read(int channel){
	int Ain,AinLow;
	ADMUX = ADMUX|(channel); /* Set input channel to read */
	ADCSRA |= (1<<ADSC); /* Start conversion */
	while((ADCSRA & (1<<ADIF)) == 0);/* Monitor end of conversion interrupt */
	_delay_us(10);
	AinLow = (int)ADCL; /* Read lower byte*/
	Ain = (int)ADCH*256; /* Read higher 2 bits and Multiply with weight */
	Ain = Ain + AinLow;
	return(Ain); /* Return digital value*/
}

int main(void)
{
	DDRC=0xFF; //sets portc as output
	DDRD=0xFF; ////sets portd as output
	DDRA=0x00;// sets ADC- portA as input
	
	//ADC  Set up
	ADCSRA = 0b10000111; //Enable pin is turned on bit 7=1 and presclaler 111(last 3 bits) to divide 8MHz freq by 128
	ADMUX = 0b00000000; // sets ADC ref as VCC(01)bit 6 and 7,5th bit sets ADCL =8bits and ADcH=2 bits,bit 0-4 sets the ADC pin to use 00000=ADC0
	
	while (1)
	{
		Potval = ADC_Read(0); /* Reads 10but ADC channel in integers 0-1023 */
		MapedValue=Potval*0.0967742;//maps from 0-1023 t0 0-99
		tens = MapedValue/10;
		ones = MapedValue%10;
		display_1(tens);
		display_2(ones);
		
	}
	return 0;
}


void display_1(int digit){
	PORTC = numbers[digit];
}
void display_2(int digit){
	PORTD = numbers[digit];
}

