/*
 * Scroll_Custom_Characters.c
 *
 * Created: 3/1/2023 4:19:40 PM
 * Author : Administrator
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_Code.h"

/*Array to store hexadecimal values for custom characters */

const short Custorm_Chars5X8[] = {
    0x0e,0x1b,0x11,0x11,0x1f,0x1f,0x1f,0x00,//Battery
	0x0a,0x0a,0x1f,0x1f,0x1f,0x0e,0x04,0x00,//Charger
	0x1f,0x15,0x15,0x0e,0x04,0x04,0x04,0x00,//Network1
	0x01,0x01,0x05,0x05,0x15,0x15,0x15,0x00,//Network2
	0x0a,0x0a,0x1f,0x11,0x11,0x0e,0x04,0x00,//Charger full
	0x04,0x16,0x0f,0x04,0x0f,0x16,0x04,0x00,//Bluetooth
	0x04,0x0e,0x0e,0x0e,0x1f,0x00,0x0e,0x00,// Bell
	0x03,0x03,0x05,0x09,0x0b,0x1b,0x18,0x00 // Music
};

void Load_Custom_Char(){
	/*Load custom char into the CGROM*/
	LCD_Cmd(0x40); // Set CGRAM Address
	for (int i = 0; i <= 63; i++){
		LCD_Char(Custorm_Chars5X8[i]);
		//LCD_String(" ");
	}
	LCD_Cmd(0x80); // Return to Home
}

int main(void)
{
    LCD_Init(); /* Initialize LCD */
    Load_Custom_Char(); /* Load custom characters into CGRAM */
    LCD_Clear(); /* Clear LCD */
	LCD_String("Custom Chars");/* Display string on screen */
	//_delay_ms(1000);
	LCD_Cmd(0xC0); /* Place cursor on the second row */
	LCD_Char(0x00); /* Display the character in address 0x00 of CGRAM*/
	LCD_String(" ");
	LCD_Char(0X01);
	LCD_String(" ");
	LCD_Char(0x02);
	LCD_Char(0x03);
	LCD_String(" ");
	LCD_Char(0x04);
	LCD_String(" ");
	LCD_Char(0x05);
	LCD_String(" ");
	LCD_Char(0x06);
	LCD_String(" ");
	LCD_Char(0x07);
	_delay_ms(1000);
	for(int i=0; i<=13; i++){
		LCD_Cmd(0X18);
		_delay_ms(500);
	}
	for(int i=0; i<=13; i++){
		LCD_Cmd(0X1C);
		_delay_ms(500);
	}
	//_delay_ms(2000);
    while (1) {
			
    }
	return(0);
}

