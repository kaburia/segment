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
#include "motor.h"
#include <stdlib.h>



int main(void)
{
    // Initialize the LCD
    LCD_Init();
    ADC_Init(); // Initialize ADC
    PWM_init(); // Initialize PWM
    interrupt_setup(); // Initialize interrupts
    timer_setup(); // Initialize timer
    LCD_String("THE MATRIX!!");
    // Read the data from the keypad
    // int value = read_keypad();

    while (1) 
    {
        read_keypad();
    }
}
