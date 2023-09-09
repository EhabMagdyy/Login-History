/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : app.c            ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#include "app.h"

int main(void)
{
	u8 second = 0, minute = 0, hour = 0, day = 0, month = 0, year = 0, dummy,
	   num_of_logins = 0, new_address = 0;

	I2C_voidMasterInit();
	SPI_voidInit();
	LCD_voidInit();

	num_of_logins = EEPROM_u8ReadDataByte(NUM_OF_LOGINS_ADD);
	/* No Previous logins */
	if(0x00 == num_of_logins || 0xFF == num_of_logins)
	{
		LCD_voidSendStringPos(1, 2, "No Prev Logins");
		_delay_ms(1000);
		LCD_voidSendCommand(LCD_CLEAR);
		LCD_voidSendCommand(LCD_DISPLAY_OFF);
		LCD_voidSendStringPos(1, 1, "Time: 00:00:00");
		LCD_voidSendStringPos(2, 1, "Date: 00/00/00");
		LCD_voidSendCommand(LCD_DISPLAY_ON);

		num_of_logins = 0;
		EEPROM_voidWriteDataByte(NUM_OF_LOGINS_ADD, 0x00);
	}
	else
	{
		Display_NumOf_Logins(num_of_logins);
		Display_Date(num_of_logins-1);
	}

	while(1)
	{
		second = SPI_voidTransReceiveData(dummy);
		minute = SPI_voidTransReceiveData(dummy);
		hour   = SPI_voidTransReceiveData(dummy);
		day    = SPI_voidTransReceiveData(dummy);
		month  = SPI_voidTransReceiveData(dummy);
		year   = SPI_voidTransReceiveData(dummy);

		new_address = num_of_logins * 8;

		EEPROM_voidWriteDataByte((SECOND_ADD + new_address) , second);
		EEPROM_voidWriteDataByte((MINUTE_ADD + new_address) , minute);
		EEPROM_voidWriteDataByte((HOUR_ADD   + new_address) , hour);
		EEPROM_voidWriteDataByte((DAY_ADD    + new_address) , day);
		EEPROM_voidWriteDataByte((MONTH_ADD  + new_address) , month);
		EEPROM_voidWriteDataByte((YEAR_ADD   + new_address) , year);

		num_of_logins++;
		EEPROM_voidWriteDataByte(NUM_OF_LOGINS_ADD, num_of_logins);

		Display_NumOf_Logins(num_of_logins);
		Display_Date(num_of_logins-1);
	}

	return 0;
}

void Display_Date(u8 num_of_logins)
{
	u8 second = 0, minute = 0, hour = 0, day = 0, month = 0, year = 0, new_address;

	new_address = num_of_logins * 8;

	second = EEPROM_u8ReadDataByte((SECOND_ADD + new_address));
	minute = EEPROM_u8ReadDataByte((MINUTE_ADD + new_address));
	hour   = EEPROM_u8ReadDataByte((HOUR_ADD   + new_address));
	day    = EEPROM_u8ReadDataByte((DAY_ADD    + new_address));
	month  = EEPROM_u8ReadDataByte((MONTH_ADD  + new_address));
	year   = EEPROM_u8ReadDataByte((YEAR_ADD   + new_address));

	LCD_voidSendCommand(LCD_DISPLAY_OFF);
	LCD_voidSendStringPos(1, 1, "Time:   :  :");
	LCD_voidSendStringPos(2, 1, "Date:   /  /");

	LCD_voidSendCharPos(1, 7 , (hour >> 4)     + '0');
	LCD_voidSendCharPos(1, 8 , (hour & 0x0F)   + '0');
	LCD_voidSendCharPos(1, 10, (minute >> 4)   + '0');
	LCD_voidSendCharPos(1, 11, (minute & 0x0F) + '0');
	LCD_voidSendCharPos(1, 13, (second >> 4)   + '0');
	LCD_voidSendCharPos(1, 14, (second & 0x0F) + '0');
	LCD_voidSendCharPos(2, 7 , (day >> 4)      + '0');
	LCD_voidSendCharPos(2, 8 , (day & 0x0F)    + '0');
	LCD_voidSendCharPos(2, 10, (month >> 4)    + '0');
	LCD_voidSendCharPos(2, 11, (month & 0x0F)  + '0');
	LCD_voidSendCharPos(2, 13, (year >> 4)     + '0');
	LCD_voidSendCharPos(2, 14, (year & 0x0F)   + '0');
	LCD_voidSendCommand(LCD_DISPLAY_ON);
}

void Display_NumOf_Logins(u8 num_of_logins)
{
	LCD_voidSendCommand(LCD_CLEAR);
	LCD_voidSendCommand(LCD_DISPLAY_OFF);
	LCD_voidSendStringPos(1, 1, "Number of logins");
	LCD_voidSendCharPos(2, 4, (num_of_logins / 10) + '0');
	LCD_voidSendCharPos(2, 5, (num_of_logins % 10) + '0');
	LCD_voidSendStringPos(2, 6, " Logins");
	LCD_voidSendCommand(LCD_DISPLAY_ON);
	_delay_ms(1500);
	LCD_voidSendCommand(LCD_CLEAR);
}
