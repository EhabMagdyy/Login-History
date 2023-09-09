/******************************************************************
**********************  Author: Ehab Magdy    *********************
**********************	File  : master.c	  *********************
**********************	Date  : 06 Sep, 2023  *********************
*******************************************************************/

#include "master.h"

Std_ReturnType ret = E_NOT_OK;

pin_config_t SPI_SS ={.port = PORTA_INDEX, .pin = GPIO_PIN5,
                      .direction = GPIO_DIRECTION_OUTPUT, .logic = GPIO_HIGH};

mssp_i2c_t i2c = {
    .i2c_clock = 100000,
    .i2c_cfg.i2c_mode = I2C_MSSP_MASTER_MODE,
    .i2c_cfg.i2c_mode_cfg = I2C_MASTER_MODE_DEFINED_CLOCK,
    .i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE,
    .i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE,
};

mssp_spi_t spi = {
    .mode = MSSP_SPI_MASTER_MODE_CLK_FOSC_DIV_64,
    .idle_state = MSSP_SPI_IDLE_STATE_LOW,
    .sample_pos = MSSP_SPI_SAMPLE_AT_MID,
    .sampling_edge = MSSP_SPI_SAMPLE_ON_IDLE_TO_ACTIVE
};

uint8 login_status;
uint8 spi_dummy;

int main()
{
    application_init();
    MSSP_I2C_Intiailize(&i2c);
    
    gpio_pin_intialize(&SPI_SS);
    
    while(1)
    {
        login_status = login_system();
        
        if(LOGIN_SUCCESSFULLY == login_status)
        {
            /* Get Date & Time */
            RTC_Get_Date_Time(&rtc);
            
            /* DeInitialize MSSP I2C Module */
            ret = MSSP_I2C_DeIntiailize();
            
            /* Initialize MSSP SPI Module + Send data */
            ret = MSSP_SPI_Intiailize(&spi);
            gpio_pin_write_logic(&SPI_SS, GPIO_LOW);
            ret = MSSP_SPI_Trancieve(rtc.second, &spi_dummy);
            ret = MSSP_SPI_Trancieve(rtc.minute, &spi_dummy);
            ret = MSSP_SPI_Trancieve(rtc.hour, &spi_dummy);
            ret = MSSP_SPI_Trancieve(rtc.day, &spi_dummy);
            ret = MSSP_SPI_Trancieve(rtc.month, &spi_dummy);
            ret = MSSP_SPI_Trancieve(rtc.year, &spi_dummy);
            
            while('#' != keypad_read_value());
            lcd_4bit_send_command(&lcd, LCD_CLEAR);
            /* DeInitialize MSSP SPI Module */
            ret = MSSP_SPI_Intiailize(&spi);
            gpio_pin_write_logic(&SPI_SS, GPIO_HIGH);
            
            /* Initialize MSSP I2C Module */
            ret = MSSP_I2C_Intiailize(&i2c);
        }
        else{/* Nothing */}
    }
    return (0);
}

void application_init(void)
{
    ecu_init();
}

/* Read keypad value */
uint8 keypad_read_value()
{
    uint8 keypad_pressed_value = 0;
    do {
        __delay_ms(20);
        ret = keypad_get_value(&keypad, &keypad_pressed_value);
    } while(0 == keypad_pressed_value);
    __delay_ms(DEBOUNE_TIME);
    return keypad_pressed_value;  
}

uint8 login_system(void)
{
	uint16 system_password = 2365, entered_password = 0;
	uint8 keypad_pressed_key = 0, pass_len = 0, num_of_tries = 0, cursor_index = 12;

	while(3 > num_of_tries)
	{
		lcd_4bit_send_string_pos(&lcd, 1, 1,"Enter Password:");
		/* Password length = 4 */
		while(4 > pass_len)
		{
			do
			{
				keypad_pressed_key = keypad_read_value();
			} while('0' > keypad_pressed_key);
            
			pass_len++;
			entered_password = (entered_password * 10) + (keypad_pressed_key - '0');

			lcd_4bit_send_char_pos(&lcd, 2 , ++cursor_index, keypad_pressed_key);
			__delay_ms(250);
			lcd_4bit_send_char_pos(&lcd, 2 , cursor_index, '*');
		}

		lcd_4bit_send_command(&lcd, LCD_CLEAR);
		/* If password correct */
		if(entered_password == system_password)
		{
			lcd_4bit_send_string_pos(&lcd, 1, 5,"Welcome!");

			return LOGIN_SUCCESSFULLY;
		}
		else
		{
			if(2 == num_of_tries)
			{
				lcd_4bit_send_string_pos(&lcd, 1, 2, "Wrong Password");
				lcd_4bit_send_string_pos(&lcd, 2, 3, "Login Denied");
                __delay_ms(1000);
                lcd_4bit_send_command(&lcd, LCD_CLEAR);
                
                lcd_4bit_send_string_pos(&lcd, 1, 2, "Wait   Seconds");
				for(uint8 sec_counter = '9' ; sec_counter >= '0' ; sec_counter--)
				{
					lcd_4bit_send_char_pos(&lcd, 1, 7, sec_counter);
					__delay_ms(1000);
				}
                lcd_4bit_send_command(&lcd, LCD_CLEAR);
			}
			else
			{
				lcd_4bit_send_string_pos(&lcd, 1, 2, "Wrong Password");
				lcd_4bit_send_char_pos(&lcd, 2, 4, (2 - num_of_tries) + '0');
				lcd_4bit_send_string_pos(&lcd, 2, 5, " Try left");
				/* Resetting variables */
				cursor_index = 12;
				pass_len = 0;
				entered_password = 0;
			}

			__delay_ms(1000);
			lcd_4bit_send_command(&lcd, LCD_CLEAR);
			num_of_tries++;
		}
	}

	return LOGIN_DENIED;
}
