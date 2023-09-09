/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : keypad.h         ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#ifndef KEYPAD_H
#define	KEYPAD_H

/* --------------------------- Includes ---------------------------- */
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/LIB_STD_Types.h"

/* ---------------------- Macro Declarations ----------------------- */
#define KEYPAD_ROWS     4
#define KEYPAD_COLOUMNS 3

/*---------------------- Data Types Declarations --------------------- */
typedef struct{
    pin_config_t keypad_rows_pins[KEYPAD_ROWS];
    pin_config_t keypad_coloumns_pins[KEYPAD_COLOUMNS];
}keypad_t;

/*----------------------- Function Declarations ---------------------- */
Std_ReturnType keypad_intialize(const keypad_t *keypad);
Std_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value);

#endif	/* KEYPAD_H */

