/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : keypad.c         ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#include "keypad.h"

static const uint8 keypad_matrix[KEYPAD_ROWS][KEYPAD_COLOUMNS] = {
                                                        {'1','2','3'},
                                                        {'4','5','6'},
                                                        {'7','8','9'},
                                                        {'*','0','#'}
};

Std_ReturnType keypad_intialize(const keypad_t *keypad){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != keypad){
        ret = E_OK;
        for(int rows_counter = 0 ; rows_counter < KEYPAD_ROWS ; rows_counter++){
            ret = gpio_pin_intialize(&(keypad->keypad_rows_pins[rows_counter]));
        }
        for(int col_counter = 0 ; col_counter < KEYPAD_COLOUMNS ; col_counter++){
            ret = gpio_pin_direction_intialize(&(keypad->keypad_coloumns_pins[col_counter]));
        }
    }
    return ret;
}

Std_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != keypad && NULL != value){
        ret = E_OK;
        uint8 logic = 0;
        for(uint8 rows = 0 ; rows < KEYPAD_ROWS ; rows++){
            ret = gpio_pin_write_logic(&(keypad->keypad_rows_pins[rows]), GPIO_HIGH);
            for(uint8 col = 0 ; col < KEYPAD_COLOUMNS ; col++){
                ret = gpio_pin_read_logic(&(keypad->keypad_coloumns_pins[col]), &logic);
                if(GPIO_HIGH == logic){
                    *value = keypad_matrix[rows][col];
                }
            }
            ret = gpio_pin_write_logic(&(keypad->keypad_rows_pins[rows]), GPIO_LOW);
        }
    }
    return ret;
}
