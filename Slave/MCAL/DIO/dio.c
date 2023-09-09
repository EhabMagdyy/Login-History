/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : dio.c            ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#include <avr/io.h>
#include "../../Library/STD_Types.h"
#include "../../Library/BIT_Math.h"

#include "dio.h"

static volatile u8* DDR_Registers[4] = {&DDRA, &DDRB, &DDRC, &DDRD};
static volatile u8* PORT_Registers[4] = {&PORTA, &PORTB, &PORTC, &PORTD};
static volatile u8* PIN_Registers[4] = {&PINA, &PINB, &PINC, &PIND};

void DIO_voidSetPinDirection(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Direction)
{
	if(MAX_PORT_NUMBER > copy_u8Port && MAX_PIN_NUMBER > copy_u8Pin)
	{
		switch(copy_u8Direction)
		{
			case DIO_DIRECTION_INPUT:  CLEAR_BIT(*(DDR_Registers[copy_u8Port]), copy_u8Pin); break;
			case DIO_DIRECTION_OUTPUT: SET_BIT(*(DDR_Registers[copy_u8Port]), copy_u8Pin);   break;
			default : /* invalid argument */;
		}
	}
	else {/* invalid argument */}
}

void DIO_voidSetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value)
{
	if(MAX_PORT_NUMBER > copy_u8Port && MAX_PIN_NUMBER > copy_u8Pin)
	{
		switch(copy_u8Value)
		{
			case DIO_LOW:  CLEAR_BIT(*(PORT_Registers[copy_u8Port]), copy_u8Pin); break;
			case DIO_HIGH: SET_BIT(*(PORT_Registers[copy_u8Port]), copy_u8Pin);   break;
			default : /* invalid argument */;
		}
	}
	else {/* invalid argument */}
}

u8 DIO_u8GetPinLogic(u8 copy_u8Port, u8 copy_u8Pin)
{
	u8 pin_value = 0;
	if(MAX_PORT_NUMBER > copy_u8Port && MAX_PIN_NUMBER > copy_u8Pin)
	{
		pin_value = READ_BIT(*(PIN_Registers[copy_u8Port]), copy_u8Pin);
	}
	else {/* invalid argument */}

	return pin_value;
}

void DIO_voidTogglePinvalue(u8 copy_u8Port, u8 copy_u8Pin)
{
	if(MAX_PORT_NUMBER > copy_u8Port && MAX_PIN_NUMBER > copy_u8Pin)
	{
         TOGGLE_BIT(*(PORT_Registers[copy_u8Port]), copy_u8Pin);
	}
	else {/* invalid argument */}
}

void DIO_voidSetPortDirection(u8 copy_u8Port, u8 copy_u8Direction)
{
	if(MAX_PORT_NUMBER > copy_u8Port)
	{
		*(DDR_Registers[copy_u8Port]) = copy_u8Direction;
	}
	else {/* invalid argument */}
}

void DIO_voidSetPortValue(u8 copy_u8Port, u8 copy_u8Value)
{
	if(MAX_PORT_NUMBER > copy_u8Port)
	{
		*(PORT_Registers[copy_u8Port]) = copy_u8Value;
	}
	else {/* invalid argument */}
}
