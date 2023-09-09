/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : I2C.c            ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#include <avr/io.h>

#include "../../Library/STD_Types.h"
#include "../../Library/BIT_Math.h"

#include "I2C.h"


void I2C_voidMasterInit (void)
{
	/* Select I2C Friq = 100 KHZ */
	/* Set Prescaler => 1*/
	CLEAR_BIT (TWSR , TWPS0);
	CLEAR_BIT (TWSR , TWPS1);
	/* Set Bit Rate Register Value = 64 */
	TWBR = 64 ;
	/* Enable ACK */
	SET_BIT (TWCR , TWEA);
	/* Enable I2C */
	SET_BIT (TWCR , TWEN);
}

void I2C_voidSlaveInit (u8 Copy_u8SlaveAddress)
{
	/* Write Slave Address */
	TWAR = Copy_u8SlaveAddress << 1 ;
	/* Enable ACK */
	SET_BIT (TWCR , TWEA);
	/* Enable I2C */
	SET_BIT (TWCR , TWEN);
}

void I2C_voidStartCondition (void)
{
	/* Clear Flag + Enable Start Condition */
	SET_BIT (TWCR , TWSTA) ;
	SET_BIT (TWCR , TWINT) ;
	
	/* Check Flag */
	while ((READ_BIT(TWCR , TWINT)) == 0);
}

void I2C_voidStopCondition  (void)
{
	/* Enable Stop Condition + Clear Flag */
	SET_BIT (TWCR , TWSTO) ;
	SET_BIT (TWCR , TWINT) ;
}

void I2C_voidSlaveAddresssWrite (u8 Copy_u8SlaveAddress)
{
	/* Select Slave Address + Write bit */
	TWDR = Copy_u8SlaveAddress << 1 ;
	CLEAR_BIT (TWDR , 0);
	
	/* Clear Start Condition */
	CLEAR_BIT (TWCR , TWSTA) ;

	/* Clear Flag */
	SET_BIT (TWCR , TWINT) ;
	
	/* Wait Flag */
	while ((READ_BIT(TWCR , TWINT)) == 0);
}

void I2C_voidSlaveAddresssRead(u8 Copy_u8SlaveAddress)
{
	/* Select Slave Address + Read bit */
	TWDR = Copy_u8SlaveAddress << 1 ;
	SET_BIT (TWDR , 0);
	/* Clear Start Condition */
	CLEAR_BIT (TWCR , TWSTA) ;
	/* Clear Flag */
	SET_BIT (TWCR , TWINT) ;
	/* Wait Flag */
	while ((READ_BIT(TWCR , TWINT)) == 0);
}


void I2C_voidMasterSendData(u8 Copy_u8Data)
{
	/* Write Data in TWDR */
	TWDR = Copy_u8Data ;
	/* Clear Flag*/
	SET_BIT (TWCR , TWINT) ;
	/* Wait Flag */
	while ((READ_BIT(TWCR , TWINT)) == 0);
}

void I2C_u8MasterRecieveData (u8* copy_u8RecData)
{
	if(NULL != copy_u8RecData)
	{
		/* Clear Flag */
		SET_BIT (TWCR , TWINT) ;
		/* Wait Flag */
		while ((READ_BIT(TWCR , TWINT)) == 0);
		/* Receive data */
		*copy_u8RecData = TWDR;
		/* Send NACK */
		CLEAR_BIT (TWCR , TWEA);
		/* Wait Flag */
		while ((READ_BIT(TWCR , TWINT)) == 0);
	}
}

u8 I2C_u8SlaveRecieveData (void)
{
	/* Wait to Master Write Address */
	while ((TWSR & 0xf8) != 0x60);
	/* Clear Flag */
	SET_BIT(TWCR , TWINT) ;
	/* Wait to Master Write Data */
	while ((TWSR & 0xf8) != 0x80);
	
	return TWDR ;
}
