/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : gpio.c           ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#include "gpio.h"

volatile uint8 *tris_registers[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *port_registers[] = {&PORTA,&TRISB,&PORTC,&PORTD,&PORTE};
volatile uint8 *lat_registers[]  = {&LATA,&LATB,&LATC,&LATD,&LATE};

Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        switch(_pin_config->direction){
            case GPIO_DIRECTION_OUTPUT:   
                CLEAR_BIT(*tris_registers[_pin_config->port] , _pin_config->pin);
                break;
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_registers[_pin_config->port] , _pin_config->pin);
                break;
            default:    ret = E_NOT_OK;
        }
    }
    return ret;
}

Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, uint8 *direction_status){
    Std_ReturnType ret = E_OK;
    if(_pin_config == NULL || direction_status == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *direction_status = READ_BIT(*tris_registers[_pin_config->port] , _pin_config->pin);
    }
    return ret;
}

Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, uint8 logic){
    Std_ReturnType ret = E_OK;
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        switch(logic){
            case GPIO_LOW:
                CLEAR_BIT(*lat_registers[_pin_config->port] , _pin_config->pin);
                break;
            case GPIO_HIGH:
                SET_BIT(*lat_registers[_pin_config->port] , _pin_config->pin);
                break;
            default:    ret = E_NOT_OK;
        }
    }
    return ret;
}

Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, uint8 *logic){
    Std_ReturnType ret = E_OK;
    if(_pin_config == NULL || logic == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *logic = READ_BIT(*port_registers[_pin_config->port] , _pin_config->pin);
    }
    return ret;    
}

Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*lat_registers[_pin_config->port] , _pin_config->pin);
    }
    return ret;    
}

Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(_pin_config == NULL || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(_pin_config);
        ret = gpio_pin_write_logic(_pin_config,_pin_config->logic);
    }
    return ret; 
}

Std_ReturnType gpio_port_direction_intialize(uint8 port, uint8 direction){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *tris_registers[port] = direction;
    }
    return ret;    
}

Std_ReturnType gpio_port_get_direction_status(uint8 port, uint8 *direction_status){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1 || direction_status == NULL){
        ret = E_NOT_OK;
    }
    else{
        *direction_status = *tris_registers[port];
    }
    return ret;    
}

Std_ReturnType gpio_port_write_logic(uint8 port, uint8 logic){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *lat_registers[port] = logic;
    }
    return ret;    
}

Std_ReturnType gpio_port_read_logic(uint8 port, uint8 *logic){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1 || logic == NULL){
        ret = E_NOT_OK;
    }
    else{
        *logic = *port_registers[port];
    }
    return ret;    
}

Std_ReturnType gpio_port_toggle_logic(uint8 port){
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *lat_registers[port] ^= PORT_MASK;   
    }
    return ret;    
}