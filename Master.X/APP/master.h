/******************************************************************
**********************  Author: Ehab Magdy    *********************
**********************	File  : master.h	  *********************
**********************	Date  : 06 Sep, 2023  *********************
*******************************************************************/

#ifndef MASTER_H
#define MASTER_H

/* --------------------------- Includes ---------------------------- */
#include "../MCAL/I2C/i2c.h"
#include "../MCAL/SPI/spi.h"
#include "../ECU/ecu_layer_init.h"

/* ---------------------- Macro Declarations ----------------------- */
#define DEBOUNE_TIME           200
#define LOGIN_DENIED            0
#define LOGIN_SUCCESSFULLY      1

/*----------------------- Function Declarations -------------------- */
void application_init(void);
uint8 keypad_read_value();
uint8 login_system(void);

#endif	/* MASTER_H */

