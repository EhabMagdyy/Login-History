/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : ecu_layer_init.c ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#include "ecu_layer_init.h"

keypad_t keypad = 
{
    .keypad_rows_pins[0].port = PORTD_INDEX,
    .keypad_rows_pins[0].pin = GPIO_PIN0,
    .keypad_rows_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[0].logic = GPIO_LOW,
    .keypad_rows_pins[1].port = PORTD_INDEX,
    .keypad_rows_pins[1].pin = GPIO_PIN1,
    .keypad_rows_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[1].logic = GPIO_LOW,
    .keypad_rows_pins[2].port = PORTD_INDEX,
    .keypad_rows_pins[2].pin = GPIO_PIN2,
    .keypad_rows_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[2].logic = GPIO_LOW,
    .keypad_rows_pins[3].port = PORTD_INDEX,
    .keypad_rows_pins[3].pin = GPIO_PIN3,
    .keypad_rows_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[3].logic = GPIO_LOW,
    
    .keypad_coloumns_pins[0].port = PORTD_INDEX,
    .keypad_coloumns_pins[0].pin = GPIO_PIN4,
    .keypad_coloumns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_coloumns_pins[0].logic = GPIO_LOW,
    .keypad_coloumns_pins[1].port = PORTD_INDEX,
    .keypad_coloumns_pins[1].pin = GPIO_PIN5,
    .keypad_coloumns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_coloumns_pins[1].logic = GPIO_LOW,
    .keypad_coloumns_pins[2].port = PORTD_INDEX,
    .keypad_coloumns_pins[2].pin = GPIO_PIN6,
    .keypad_coloumns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_coloumns_pins[2].logic = GPIO_LOW,
};

lcd_4bit_t lcd = 
{
    .lcd_rs.port = PORTB_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_enable.port = PORTB_INDEX,
    .lcd_enable.pin = GPIO_PIN1,
    .lcd_enable.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_enable.logic = GPIO_LOW,
    
    .data_lines[0].port = PORTB_INDEX,
    .data_lines[0].pin = GPIO_PIN2,
    .data_lines[0].direction = GPIO_DIRECTION_OUTPUT,
    .data_lines[0].logic = GPIO_LOW,
    .data_lines[1].port = PORTB_INDEX,
    .data_lines[1].pin = GPIO_PIN3,
    .data_lines[1].direction = GPIO_DIRECTION_OUTPUT,
    .data_lines[1].logic = GPIO_LOW,
    .data_lines[2].port = PORTB_INDEX,
    .data_lines[2].pin = GPIO_PIN4,
    .data_lines[2].direction = GPIO_DIRECTION_OUTPUT,
    .data_lines[2].logic = GPIO_LOW,
    .data_lines[3].port = PORTB_INDEX,
    .data_lines[3].pin = GPIO_PIN5,
    .data_lines[3].direction = GPIO_DIRECTION_OUTPUT,
    .data_lines[3].logic = GPIO_LOW
};

RTC_t rtc;

void ecu_init(void)
{
    keypad_intialize(&keypad);
    lcd_4bit_intialize(&lcd);
}