/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : lcd.c            ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#include "../../Library/STD_Types.h"
#include "../../MCAL/DIO/dio.h"
#include "util/delay.h"

#include "lcd.h"

void LCD_voidInit(void)
{
	/* Data pins -> output */
	DIO_voidSetPortDirection(LCD_DATA_PORT, 0xFF);
	
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, LCD_EN_PIN, DIO_DIRECTION_OUTPUT);
	_delay_ms(40);

    /* Set LCD Configurations */
	LCD_voidSendCommand(LCD_Function_SET);
	_delay_us(40);
	LCD_voidSendCommand(LCD_DISPLAY_ON);
	_delay_us(40);
	LCD_voidSendCommand(LCD_CLEAR);
	_delay_ms(2);
	LCD_voidSendCommand(LCD_INCREMENT_SHIFT_OFF);
	_delay_ms(2);
}

void LCD_voidSendCommand(u8 command)
{
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_LOW);
	/* send command */
	DIO_voidSetPortValue(LCD_DATA_PORT, command);
	/* Send enable signal */
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, DIO_HIGH);
	_delay_us(5);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, DIO_LOW);
}

void LCD_voidSendChar(u8 data)
{
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_HIGH);
	/* send data */
	DIO_voidSetPortValue(LCD_DATA_PORT, data);
	/* Send enable signal */
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, DIO_HIGH);
	_delay_us(5);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, DIO_LOW);
}

void LCD_voidSendCharPos(u8 row, u8 col, u8 data)
{
	LCD_voidSetCursor(row, col);
	LCD_voidSendChar(data);
}

void LCD_voidSendString(u8 *string)
{
	while(*string){
		LCD_voidSendChar(*string);
		string++;
	}
}

void LCD_voidSendStringPos(u8 row, u8 col, u8 *string)
{
	LCD_voidSetCursor(row, col);
	LCD_voidSendString(string);
}

void LCD_voidDrawCharacter(u8 *custom_char, u8 pos)
{
	if(NULL != custom_char){
		LCD_voidSendCommand(LCD_CGRAM + pos * 8);
		_delay_us(50);
		for(u8 char_index = 0 ; char_index < 8 ; char_index++){
			LCD_voidSendChar(custom_char[char_index]);
		}
		LCD_voidSendChar(pos);
	}
}

void LCD_voidSetCursor(u8 row, u8 col)
{
	if(3 > row && 17 > col){
		col--;

		switch(row)
		{
			case ROW1: LCD_voidSendCommand(0x80 + col); break;
			case ROW2: LCD_voidSendCommand(0xC0 + col); break;
			default: break;
		}
	}
}
