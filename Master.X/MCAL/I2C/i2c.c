/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : i2c.c            ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#include "i2c.h"

static inline void MSSP_I2C_Mode_GPIO_CFG();
static inline void MSSP_I2C_Master_Mode_Clock_Configuration(const uint32 i2c_clock);
static inline void MSSP_I2C_Slave_Mode_Configuration(const uint8 i2c_mode_cfg);

Std_ReturnType MSSP_I2C_Intiailize(const mssp_i2c_t* i2c_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != i2c_obj)
    {
        ret = E_OK;
        /* Disable MSSP I2C Module */
        MSSP_MODULE_DISABLE_CFG();
        /* MSSP I2C Select Mode */
        if(I2C_MSSP_MASTER_MODE == i2c_obj->i2c_cfg.i2c_mode){
            MSSP_I2C_Master_Mode_Clock_Configuration(i2c_obj->i2c_clock);
        }
        else if(I2C_MSSP_SLAVE_MODE == i2c_obj->i2c_cfg.i2c_mode){
            /* I2C Slave Mode General Call Configurations */
            if(I2C_GENERAL_CALL_ENABLE == i2c_obj->i2c_cfg.i2c_general_call){
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if(I2C_GENERAL_CALL_DISABLE == i2c_obj->i2c_cfg.i2c_general_call){
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            else { /* Nothing */ }
            /* Clear the Write Collision Detect */
            SSPCON1bits.WCOL = 0; /* No Collision */
            /* Clear the Receive Overflow Indicator */
            SSPCON1bits.SSPOV = 0; /* No Overflow */
            /* Release the clock */
            SSPCON1bits.CKP = 1;
            /* Assign the I2C Slave Address */
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_address;
            /* I2C Slave Mode Configurations */
            MSSP_I2C_Slave_Mode_Configuration(i2c_obj->i2c_cfg.i2c_mode_cfg);
        }
        else {/* Nothing */}
        /* MSSP I2C GPIO Configurations */
        MSSP_I2C_Mode_GPIO_CFG();
        /* MSSP I2C Slew Rate Control */
        if(I2C_SLEW_RATE_DISABLE == i2c_obj->i2c_cfg.i2c_slew_rate){
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        else if(I2C_SLEW_RATE_ENABLE == i2c_obj->i2c_cfg.i2c_slew_rate){
            I2C_SLEW_RATE_ENABLE_CFG();
        }
        else { /* Nothing */ }
        /* MSSP I2C SMBus Control */
        if(I2C_SMBus_ENABLE == i2c_obj->i2c_cfg.i2c_SMBus_control){
            I2C_SMBus_ENABLE_CFG();
        }
        else if(I2C_SMBus_DISABLE == i2c_obj->i2c_cfg.i2c_SMBus_control){
            I2C_SMBus_DISABLE_CFG();
        }
        else { /* Nothing */ }

        /* Enable MSSP I2C Module */
        MSSP_MODULE_ENABLE_CFG();
    }
    return ret;
}

Std_ReturnType MSSP_I2C_DeIntiailize(void)
{
    Std_ReturnType ret = E_OK;
    
    /* Disable MSSP I2C Module */
    MSSP_MODULE_DISABLE_CFG();
        
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Start(void)
{
    Std_ReturnType ret = E_NOT_OK;

    /* Initiates Start condition on SDA and SCL pins */
    SSPCON2bits.SEN = 1; /* Initiates Start condition on SDA and SCL pins. Automatically cleared by hardware. */
    /* Wait for the completion of the Start condition */
    while(SSPCON2bits.SEN);
    /* Clear The MSSP Interrupt Flag bit -> SSPIF */
    PIR1bits.SSPIF = 0;
    /* Report The Start Condition Detection */
    if(I2C_START_BIT_DETECTED == SSPSTATbits.S){
        ret = E_OK; /* Indicates that a Start bit has been detected last */
    }
    else{
        ret = E_NOT_OK; /* Start bit was not detected last */
    }

    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Repeated_Satrt(void)
{
    Std_ReturnType ret = E_OK;

    /* Initiates Repeated Start condition on SDA and SCL pins */
    SSPCON2bits.RSEN = 1; /* Initiates Repeated Start condition on SDA and SCL pins. Automatically cleared by hardware */
    /* Wait for the completion of the Repeated Start condition */
    while(SSPCON2bits.RSEN);
    /* Clear The MSSP Interrupt Flag bit -> SSPIF */
    PIR1bits.SSPIF = 0;

    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Stop(void)
{
    Std_ReturnType ret = E_NOT_OK;

    /* Initiates Stop condition on SDA and SCL pins */
    SSPCON2bits.PEN = 1; /* Initiates Stop condition on SDA and SCL pins. Automatically cleared by hardware */
    /* Wait for the completion of the Stop condition */
    while(SSPCON2bits.PEN);
    /* Clear The MSSP Interrupt Flag bit -> SSPIF */
    PIR1bits.SSPIF = 0;
    /* Report The Stop Condition Detection */
    if(I2C_STOP_BIT_DETECTED == SSPSTATbits.P){
        ret = E_OK; /* Indicates that a Stop bit has been detected last */
    }
    else{
        ret = E_NOT_OK; /* Stop bit was not detected last */
    }

    return ret;
}

Std_ReturnType MSSP_I2C_Master_Write_Blocking(uint8 i2c_data, uint8 *_ack)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _ack){
        ret = E_NOT_OK;
    }
    else{
        /* Write Data to the Data register */
        SSPBUF = i2c_data;
        /* Wait The transmission to be completed */
        while(SSPSTATbits.BF);
        /* Clear The MSSP Interrupt Flag bit -> SSPIF */
        PIR1bits.SSPIF = 0;
        /* Report the acknowledge received from the slave */
        if(I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT){
            *_ack = I2C_ACK_RECEIVED_FROM_SLAVE; /* Acknowledge was received from slave */
        }
        else{
            *_ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE; /* Acknowledge was not received from slave */
        }
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Write_NBlocking(uint8 i2c_data, uint8 *_ack){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _ack){
        ret = E_NOT_OK;
    }
    else{
         
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Read_Blocking(uint8 ack, uint8 *i2c_data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == i2c_data){
        ret = E_NOT_OK;
    }
    else{
        /* Master Mode Receive Enable */
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        /* Wait for buffer full flag : A complete byte received */
        while(!SSPSTATbits.BF);
        /* Copy The data registers to buffer variable */
        *i2c_data = SSPBUF;
        /* Send ACK or NACK after read */
        if(I2C_MASTER_SEND_ACK == ack){
            SSPCON2bits.ACKDT = 0; /* Acknowledge */
            /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. */
            SSPCON2bits.ACKEN = 1; 
            while(SSPCON2bits.ACKEN); /* Automatically cleared by hardware */
        }
        else if(I2C_MASTER_SEND_NACK == ack){
            SSPCON2bits.ACKDT = 1; /* Not Acknowledge */
            /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. */
            SSPCON2bits.ACKEN = 1;
            while(SSPCON2bits.ACKEN); /* Automatically cleared by hardware */
        }
        else { /* Nothing */ }
        ret = E_OK;
    }
    return ret;
}

/* Not Sure */
Std_ReturnType MSSP_I2C_Master_Read_NonBlocking(uint8 acknowledge, uint8* data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != data)
    {
        ret = E_OK;
        /* Master Mode Receive Enable */
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        /* check if complete byte received */
        if(I2C_SSPBUF_IS_FULL == SSPSTATbits.BF){
            *data = SSPBUF;
        }
        /* Send ACK or NACK after read */
        if(I2C_MASTER_SEND_ACK == acknowledge){
            SSPCON2bits.ACKDT = 0; /* Acknowledge */
            /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. */
            SSPCON2bits.ACKEN = 1; 
            while(SSPCON2bits.ACKEN); /* Automatically cleared by hardware */
        }
        else if(I2C_MASTER_SEND_NACK == acknowledge){
            SSPCON2bits.ACKDT = 1; /* Not Acknowledge */
            /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. */
            SSPCON2bits.ACKEN = 1;
            while(SSPCON2bits.ACKEN); /* Automatically cleared by hardware */
        }
        else { /* Nothing */ }
    }
    return ret;
}

static inline void MSSP_I2C_Mode_GPIO_CFG(){
    TRISCbits.TRISC3 = 1;  /* Serial Clock (SCL) is input */
    TRISCbits.TRISC4 = 1;  /* Serial Data (SCA) is input */
}

static inline void MSSP_I2C_Master_Mode_Clock_Configuration(const uint32 i2c_clock)
{
    I2C_SELECT_MODE(I2C_MASTER_MODE_DEFINED_CLOCK);
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / i2c_clock) - 1);
}

static inline void MSSP_I2C_Slave_Mode_Configuration(const uint8 i2c_mode_cfg)
{
    I2C_SELECT_MODE(i2c_mode_cfg);
}
