/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : EEPROM.c         ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include "../../Library/STD_Types.h"
#include "../../Library/BIT_Math.h"
#include "../../MCAL/I2C/I2C.h"
#include "EEPROM.h"


void EEPROM_voidWriteDataByte (u16 Copy_u16ByteAddress , u8 Copy_u8Data)
{
	I2C_voidStartCondition();
	I2C_voidSlaveAddresssWrite(UNIQ_ADD | (A2_PIN << 2) | (Copy_u16ByteAddress >> 8));
	I2C_voidMasterSendData((u8)Copy_u16ByteAddress);
	
	I2C_voidMasterSendData( Copy_u8Data );

	I2C_voidStopCondition();
	
	_delay_ms (10);
}

u8 EEPROM_u8ReadDataByte (u16 Copy_u16ByteAddress)
{
	u8 Local_u8Data ;

	I2C_voidStartCondition();
	I2C_voidSlaveAddresssWrite(UNIQ_ADD | (A2_PIN << 2) | (Copy_u16ByteAddress >> 8));
	I2C_voidMasterSendData( (u8)Copy_u16ByteAddress );

	I2C_voidStartCondition();
	I2C_voidSlaveAddresssRead(UNIQ_ADD | (A2_PIN << 2)| (Copy_u16ByteAddress >> 8));
	
	I2C_u8MasterRecieveData(&Local_u8Data);

	I2C_voidStopCondition();
	
	return Local_u8Data ;
}
