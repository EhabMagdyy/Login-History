/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : lcd.c            ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#include "lcd.h"

static Std_ReturnType lcd_send_4bit(const lcd_4bit_t *lcd, uint8 data);
static Std_ReturnType send_4bit_enable_signal(const lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8 row, uint8 colomn);

Std_ReturnType lcd_4bit_intialize(const lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_enable));
        for(uint8 pin = 0 ; pin < 4 ; pin++){
            ret = gpio_pin_intialize(&(lcd->data_lines[pin]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        
        ret = lcd_4bit_send_command(lcd, LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, LCD_CURSOR_HOME);
        ret = lcd_4bit_send_command(lcd, LCD_INCREMENT_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, LCD_4BIT_MODE_2LINES);
        ret = lcd_4bit_send_command(lcd, LCD_DDRAM_START);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8 command)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = lcd_send_4bit(lcd, command >> 4);
        ret = send_4bit_enable_signal(lcd);
        ret = lcd_send_4bit(lcd, command);
        ret = send_4bit_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_char(const lcd_4bit_t *lcd, uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_send_4bit(lcd, data >> 4);
        ret = send_4bit_enable_signal(lcd);
        ret = lcd_send_4bit(lcd, data);
        ret = send_4bit_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_char_pos(const lcd_4bit_t *lcd, uint8 row, uint8 colomn, uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = lcd_4bit_set_cursor(lcd, row, colomn);
        ret = lcd_4bit_send_char(lcd, data);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8 *string)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        do{
            lcd_4bit_send_char(lcd, *string);
        } while(*(++string));
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8 row, uint8 colomn, uint8 *string)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = lcd_4bit_set_cursor(lcd, row, colomn);
        ret = lcd_4bit_send_string(lcd, string);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_custom_character(const lcd_4bit_t *lcd, uint8 row, uint8 colomn,
                                                const uint8 ch[], uint8 mem_pos)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = lcd_4bit_send_command(lcd, (LCD_CGRAM_START + (mem_pos * 8)));
        for(uint8 char_index = 0 ; char_index < 8 ; char_index++){
            ret = lcd_4bit_send_char(lcd, ch[char_index]);
        }
        ret = lcd_4bit_send_char_pos(lcd, row, colomn, mem_pos);
    }
    return ret;
}

static Std_ReturnType lcd_send_4bit(const lcd_4bit_t *lcd, uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        for(uint8 line_pins = 0 ; line_pins < 4 ; line_pins++){
            ret = gpio_pin_write_logic(&(lcd->data_lines[line_pins]), (data >> line_pins) & 0x01);
        }
    }
    return ret;
}

static Std_ReturnType send_4bit_enable_signal(const lcd_4bit_t *lcd)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_write_logic(&(lcd->lcd_enable), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_enable), GPIO_LOW);
    }
    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8 row, uint8 colomn)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd && row <= NUMBER_OF_ROWS && colomn <= NUMBER_OF_COLOMNS){
        colomn--; 
        switch(row){
            case ROW1: ret = lcd_4bit_send_command(lcd, (0x80 + colomn));  break;
            case ROW2: ret = lcd_4bit_send_command(lcd, (0xc0 + colomn));  break;
            default:                                                       break;
        }
    }
    return ret; 
}
