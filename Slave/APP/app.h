/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : app.h            ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#ifndef APP_H
#define APP_H

/* --------------------------- Includes ---------------------------- */
#include "../MCAL/DIO/dio.h"
#include "../HAL/LCD/lcd.h"
#include "util/delay.h"
#include "../MCAL/SPI/spi.h"
#include "../MCAL/I2C/I2C.h"
#include "../HAL/EEPROM/EEPROM.h"

/* ---------------------- Macro Declarations ----------------------- */
#define NUM_OF_LOGINS_ADD   0x00

#define HOUR_ADD		    0x08
#define MINUTE_ADD		    0x09
#define SECOND_ADD		    0x0A
#define DAY_ADD 		    0x0C
#define MONTH_ADD		    0x0D
#define YEAR_ADD		    0x0E

/*----------------------- Function Declarations ---------------------- */
void Display_Date(u8 num_of_logins);
void Display_NumOf_Logins(u8 num_of_logins);

#endif /* APP_H */
