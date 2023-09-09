/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : ecu_layer_init.h ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* --------------------------- Includes ---------------------------- */
#include "../ECU/Keypad/keypad.h"
#include "../ECU/RTC/rtc.h"
#include "../ECU/LCD/lcd.h"

/*---------------------- Data Types Declarations -------------------- */
extern keypad_t keypad;
extern lcd_4bit_t lcd;
extern RTC_t rtc;

/*----------------------- Function Declarations --------------------- */
void ecu_init(void);


#endif	/* ECU_LAYER_INIT_H */
