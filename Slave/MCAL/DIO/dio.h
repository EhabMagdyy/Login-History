/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : dio.h            ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#ifndef DIO_H_
#define DIO_H_

/* --------------------------- Includes ---------------------------- */
#include "../../Library/STD_Types.h"

/* ---------------------- Macro Declarations ----------------------- */
#define DIO_DIRECTION_INPUT		0
#define DIO_DIRECTION_OUTPUT	1

#define DIO_LOW					0
#define DIO_HIGH				1

#define DIO_PORTA		0
#define DIO_PORTB		1
#define DIO_PORTC		2
#define DIO_PORTD		3

#define DIO_PIN0		0
#define DIO_PIN1		1
#define DIO_PIN2		2
#define DIO_PIN3		3
#define DIO_PIN4		4
#define DIO_PIN5		5
#define DIO_PIN6		6
#define DIO_PIN7		7

#define MAX_PORT_NUMBER		4
#define MAX_PIN_NUMBER		8

/*----------------------- Function Declarations ---------------------- */
void DIO_voidSetPinDirection(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Direction);
void DIO_voidSetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8Value);
u8 DIO_u8GetPinLogic(u8 copy_u8Port, u8 copy_u8Pin);
void DIO_voidTogglePinvalue(u8 copy_u8Port, u8 copy_u8Pin);
void DIO_voidSetPortDirection(u8 copy_u8Port, u8 copy_u8Direction);
void DIO_voidSetPortValue(u8 copy_u8Port, u8 copy_u8Value);

#endif /* DIO_H_ */
