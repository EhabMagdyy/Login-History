/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : EEPROM.h         ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#ifndef		EEPROM_H
#define		EEPROM_H

/* --------------------------- Includes ---------------------------- */
#include "../../Library/STD_Types.h"

/*---------------------- Data Types Declarations --------------------- */
#define 	A2_PIN		0
#define		UNIQ_ADD	0x50		

/*----------------------- Function Declarations ---------------------- */
void EEPROM_voidWriteDataByte(u16 Copy_u16ByteAddress, u8 Copy_u8Data);
u8 EEPROM_u8ReadDataByte(u16 Copy_u16ByteAddress);

#endif
