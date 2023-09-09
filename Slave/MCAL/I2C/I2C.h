/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : I2C.h            ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#ifndef		I2C_H
#define		I2C_H

/* --------------------------- Includes ---------------------------- */
#include "../../Library/STD_Types.h"

/*----------------------- Function Declarations ---------------------- */
void I2C_voidMasterInit(void);
void I2C_voidSlaveInit(u8 Copy_u8SlaveAddress);

void I2C_voidStartCondition(void);
void I2C_voidStopCondition (void);

void I2C_voidSlaveAddresssWrite(u8 Copy_u8SlaveAddress);
void I2C_voidSlaveAddresssRead(u8 Copy_u8SlaveAddress);


void I2C_voidMasterSendData(u8 Copy_u8Data);
void I2C_u8MasterRecieveData(u8* Copy_u8RecData);

u8 I2C_u8SlaveRecieveData(void);

#endif
