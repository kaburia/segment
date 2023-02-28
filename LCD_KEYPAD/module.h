// library.h

#ifndef MODULE_H
#define MODULE_H

extern volatile uint8_t PORTD;
extern volatile uint8_t DDRD;

/*Function Declarations*/
void LCD_Cmd(unsigned char cmd);
void LCD_Data(unsigned char char_data);
void LCD_Init(void);
void LCD_Clear(void);
void LCD_String(char *str);
void LCD_String_xy(char row, char pos, char *str);
void Custom_characters(unsigned char custom_char[]);

#endif