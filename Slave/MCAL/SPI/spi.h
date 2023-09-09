/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : spi.h            ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/


#ifndef SPI_H
#define SPI_H

/* --------------------------- Includes ---------------------------- */
#include "../../Library/STD_Types.h"

/* ---------------------- Macro Declarations ----------------------- */
#define SPI_MASTER_MODE		0
#define SPI_SLAVE_MODE		1

#define SPI_MODE		SPI_SLAVE_MODE

/*----------------------- Function Declarations ---------------------- */
void SPI_voidInit(void);
u8 SPI_voidTransReceiveData(u8 Copy_u8Data);

#endif /* SPI_H */
