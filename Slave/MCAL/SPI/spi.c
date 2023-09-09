/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : spi.c            ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../../Library/BIT_Math.h"
#include "../../Library/STD_Types.h"
#include "../../MCAL/DIO/dio.h"

#include "spi.h"

void SPI_voidInit(void)
{
	/* Select mode */
#if SPI_MODE == SPI_MASTER_MODE
	SET_BIT(SPCR, MSTR);

	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN5, DIO_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN7, DIO_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_DIRECTION_OUTPUT);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_LOW);
#elif SPI_MODE == SPI_SLAVE_MODE
	CLEAR_BIT(SPCR, MSTR);

	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN6, DIO_DIRECTION_OUTPUT);
#endif

	/* Data Order -> MSB first - 0 */
	CLEAR_BIT(SPCR, DORD);

	/* Clock polarity -> leading OR trailing */
	CLEAR_BIT(SPCR, CPOL);

	/* Clock polarity -> SetUP - Sample at leading - trailing in order */
	SET_BIT(SPCR, CPHA);

	/* Set SCK Clock frequency -> Fosc / 128 */
	SET_BIT(SPCR, SPR0);
	SET_BIT(SPCR, SPR1);

	/* Disable double speed */
	CLEAR_BIT(SPSR, SPI2X);

	/* Enable Module */
	SET_BIT(SPCR, SPE);
}

u8 SPI_voidTransReceiveData(u8 Copy_u8Data)
{
	/* Transmit your data */
	SPDR = Copy_u8Data;
	/* Wait until transmission complete */
	/* SPIF is cleared by reading it or ISR Executed */
	while(0 == READ_BIT(SPSR, SPIF));
	/* Return received data */
	return SPDR;
}
