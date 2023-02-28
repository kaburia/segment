/*
 * GccApplication13.c
 *
 * Created: 28/02/2023 00:38:12
 * Author : Austin
 */ 

#include <avr/io.h>
#include <util/delay.h>

// LCD module connections
#define LCD_Cmd_Dir DDRD
#define LCD_Dir DDRD
#define LCD_Port PORTD
#define LCD_Cmd_Port PORTD
#define RS 0
#define EN 1
#define RW 0

// Keypad connections
#define KEY_DDR DDRC
#define KEY_PORT PORTC
#define KEY_PIN PINC
char input, rowNum, colNum;

/*Function Declarations*/
void LCD_Cmd(unsigned char cmd);
void LCD_Data(unsigned char char_data);
void LCD_Init(void);
void LCD_Clear(void);
void LCD_String(char *str);
void LCD_String_xy(char row, char pos, char *str);
void Custom_characters();
char check_Keypad(void);


unsigned char custom_char[] = {0x1F, 0x1B, 0x1F, 0x04, 0x0E, 0x1F, 0x00, 0x00};
	
/* Keypad array holding the keys in a grid arrangement*/
unsigned char keypad[4][4] = {  {'7','8','9','/'},
								{'4','5','6','*'},
								{'1','2','3','-'},
								{' ','0','=','+'}};


/*Our main program*/
int main(void)
{
	char key_pressed = ' '; // Initialize variable to store keypad button press
	LCD_Init(); /* Initialize LCD */
	LCD_String("Welcome"); /* Write a string on 1st line of LCD*/
	_delay_ms(1000);
	LCD_Cmd(0xC0); /* Go to 2nd line*/	
	//Custom_characters(custom_char);
	while (1)
	{
		key_pressed = check_Keypad();
		if (key_pressed != ' ')
		{
			char str[2] = {key_pressed, '\0'}; // Convert button press to string
			LCD_String(str); // Display button press on LCD
			// clear the key_pressed variable if all 16 in the LCD are filled
			if (LCD_Port == 0x0F)
			{
				LCD_Clear();
			}

		}
	}
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
}

void LCD_Init (void){
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
void Custom_characters(){
	// CGRAM address = (character code x 8) + CGRAM base address
	//unsigned char cgram_address = (1 * 8) + 0x40;

	LCD_Cmd(0x40); // Set CGRAM address
	for(int i=0; i<8; i++) {
		LCD_Data(custom_char[i]);
	}
	LCD_Cmd(0x80);
	
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

/* Function that checks the key that has been pressed on the keypad */
char check_Keypad()
{
    while(1)
    {
        KEY_DDR = 0xF0; // Set the rows as outputs and the columns as inputs
        KEY_PORT = 0x0F; // Set the columns HIGH and the rows LOW.
        /*With the columns HIGH and the rows LOW, thus the KEY_PIN == 0x0F(0b0000 1111).
        If a button is pressed, the value of the column pin will be grounded and
        KEY_PIN will change from 0x0F to some other number 0x0E i.e.
        0x0E(0b0000 1110) i.e. a button in the 4th column was pressed.
        */
        do
        {
            do
            {
            _delay_ms(20); // 20ms key debounce time
            colNum = (KEY_PIN & 0x0F); // read status of column
            }
            while(colNum == 0x0F); // check for any key press
            _delay_ms (40); // 20 ms key debounce time
            colNum = (KEY_PIN & 0x0F);
            }
        while(colNum == 0x0F);
            /*Once we have established which column the button is, we need to know the row
            To this we set the rows HIGH and ground them 1 pin at a time while reading the result
            on the column pins.
            */
            KEY_PORT = 0xEF; // Check for pressed key in 4th row
            asm("NOP");
            input = (KEY_PIN & 0x0F);
            if(input != 0x0F)
            {
                rowNum = 3;
                break;
            }
            KEY_PORT = 0xDF; // Check for pressed key in 3rd row
            asm("NOP");
            input = (KEY_PIN & 0x0F);
            if(input != 0x0F)
            {
                rowNum = 2;
                break;
            }
            KEY_PORT = 0xBF; // Check for pressed key in 2nd row
            asm("NOP");
            input = (KEY_PIN & 0x0F);
            if(input != 0x0F)
            {
                rowNum = 1;
                break;
            }
            KEY_PORT = 0x7F; // Check for pressed key in 1st row
            asm("NOP");
            input = (KEY_PIN & 0x0F);
            if(input != 0x0F)
            {
                rowNum = 0;
                break;
            }
    }
    /*After obtaining the column and row values, the final keypad key can be output by cross
    referencing
    the rows and columns in our keypad character array
    */
    if(colNum == 0x0E)
    return(keypad[rowNum][3]);
    else if(colNum == 0x0D)
    return(keypad[rowNum][2]);
    else if(colNum == 0x0B)
    return(keypad[rowNum][1]);
    else
    return(keypad[rowNum][0]);
}