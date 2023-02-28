/*
 * GccApplication13.c
 *
 * Created: 28/02/2023 00:38:12
 * Author : Austin
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define LCD_Cmd_Dir DDRD
#define LCD_Dir DDRD
#define LCD_Port PORTD
#define LCD_Cmd_Port PORTD
#define RS 0
#define EN 1
#define RW 0

/*Function Declarations*/
void LCD_Cmd(unsigned char cmd);
void LCD_Data(unsigned char char_data);
void LCD_Init(void);
void LCD_Clear(void);
void LCD_String(char *str);
void LCD_String_xy(char row, char pos, char *str);
void Custom_characters(unsigned char custom_char[]);

unsigned char custom_char[] = {0x0e,0x0e,0x04,0x04,0x1f,0x04,0x0a,0x0a};

/*Our main program*/
int main(void)
{
	LCD_Init(); /* Initialize LCD */
	LCD_String("Custom Chars"); /* Write a string on 1st line of LCD*/
	LCD_Cmd(0xC0); /* Go to 2nd line*/	
	Custom_characters(custom_char);
}

/*LCD command write function*/
void LCD_Cmd(unsigned char cmd){
	/*Sending the first nibble of data (Higher 4 bits)*/
	LCD_Port = (LCD_Port & 0x0F) | (cmd & 0xF0);/* Sending upper nibble */
	LCD_Port &= ~ (1<<RS); /* RS=0, command reg. */
	LCD_Port |= (1<<EN); /* Enable pulse ON */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN); /* Enable pulse OFF */
	_delay_us(200);
	/*Sending the second nibble of data (Lower 4 bits)*/
	LCD_Port = (LCD_Port & 0x0F) | (cmd << 4);/* Sending lower nibble */
	LCD_Port |= (1<<EN); /* Enable pulse ON */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN); /* Enable pulse OFF */
	_delay_ms(2);
}

/*LCD data write function */
void LCD_Data (unsigned char char_data){
	/*Sending the first nibble of data (Higher 4 bits)*/
	LCD_Port = (LCD_Port & 0x0F) | (char_data & 0xF0);/* Sending upper nibble */
	LCD_Port |= (1<<RS); /* RS=1, data reg. */
	LCD_Port |= (1<<EN); /* Enable pulse ON */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN); /* Enable pulse OFF */
	_delay_us(200);
	/*Sending the second nibble of data (Lower 4 bits)*/
	LCD_Port = (LCD_Port & 0x0F) | (char_data << 4); /* Sending lower nibble */
	LCD_Port |= (1<<EN); /* Enable pulse ON */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN); /* Enable pulse OFF */
	_delay_ms(2);
}void LCD_Init (void){
	LCD_Dir = 0xFF; /* Make LCD command port direction as output pins*/
	_delay_ms(20); /* LCD Power ON delay always > 15ms */
	LCD_Cmd(0x02); /* Return display to its home position */
	LCD_Cmd(0x28); /* 2 line 4bit mode */
	LCD_Cmd(0x0C); /* Display ON Cursor OFF */
	LCD_Cmd(0x06); /* Auto Increment cursor */
	LCD_Cmd(0x01); /* Clear display */
}

/*Clear LCD Function*/
void LCD_Clear(void){
	LCD_Cmd(0x01); /* clear display */
	LCD_Cmd(0x02); /* Return display to its home position */
}

/*Send string to LCD function */
void LCD_String (char *str){
	int i;
	/* Send each char of string till the NULL */
	for(i=0;str[i]!=0;i++){
		LCD_Data(str[i]);
	}
}

// Create custom characters
void Custom_characters(unsigned char custom_char[]){
	// CGRAM address = (character code x 8) + CGRAM base address
	unsigned char cgram_address = (1 * 8) + 0x40;

	LCD_Cmd(cgram_address); // Set CGRAM address
	for(int i=0; i<8; i++) {
		LCD_Data(custom_char[i]);
	}
	
}

/*Send string to LCD with xy position */
void LCD_String_xy (char row, char pos, char *str){
	if (row == 0 && pos<16){
		LCD_Cmd((pos & 0x0F)|0x80);/* Command of first row and required
		position<16 */
	}
	else if (row == 1 && pos<16){
		LCD_Cmd((pos & 0x0F)|0xC0);/* Command of second row and required
		position<16 */
	}
	LCD_String(str); /* Call LCD string function */
}
