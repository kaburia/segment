/*
 * GccApplication13.c
 *
 * Created: 28/02/2023 00:38:12
 * Author : Austin
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "module.h"

#define LCD_Cmd_Dir DDRD
#define LCD_Dir DDRD
#define LCD_Port PORTD
#define LCD_Cmd_Port PORTD
#define RS 0
#define EN 1
#define RW 0


unsigned char custom_char[] = {0x1F, 0x1B, 0x1F, 0x04, 0x0E, 0x1F, 0x00, 0x00};

/*Our main program*/
int main(void)
{
	LCD_Init(); /* Initialize LCD */
	LCD_String("Custom Chars"); /* Write a string on 1st line of LCD*/
	_delay_ms(1000);
	LCD_Cmd(0xC0); /* Go to 2nd line*/	
	Custom_characters(custom_char);
}

