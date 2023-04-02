/*
 * Display_motors.c
 *
 * Created: 01/04/2023 11:29:38
 * Author : Austin
 */ 

#define F_CPU 8000000UL
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "LCD.h"
#include "ADC.h"
#include <string.h>
#include <math.h>
#include "keypad.h"



int main(void)
{
    // Initialize the LCD
    LCD_Init();
    while (1) 
    {
        // Read the data from the keypad
        int value = read_keypad();
        // Display the data on the LCD
        LCD_String("Value: ");
        char str[10];
        sprintf(str, "%d", value);
        LCD_String(str);
    }
}

