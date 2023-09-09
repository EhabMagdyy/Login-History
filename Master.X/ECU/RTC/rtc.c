/******************************************************************
**********************  Author: Ehab Magdy       ******************
**********************	File  : rtc.c            ******************
**********************	Date  : 06 Sep, 2023     ******************
*******************************************************************/

#include "rtc.h"

Std_ReturnType RTC_Get_Date_Time(RTC_t* rtc_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 ack;
    /* Dummy read, Ignore it :) */
    ret = MSSP_I2C_Master_Send_Start();
    ret = MSSP_I2C_Master_Write_Blocking(RTC_ADD, &ack);
    ret = MSSP_I2C_Master_Write_Blocking(RTC_SECONDES_ADD, &ack);
    ret = MSSP_I2C_Master_Send_Repeated_Satrt();
    ret = MSSP_I2C_Master_Write_Blocking(RTC_ADD | 0x01, &ack);
    ret = MSSP_I2C_Master_Read_Blocking(I2C_MASTER_SEND_NACK, &(rtc_obj->second));
    ret = MSSP_I2C_Master_Send_Stop();
    /* Reading Time & Date */
    for(uint8 func_add = RTC_SECONDES_ADD ; func_add <= RTC_YEAR_ADD ; (2 == func_add)?func_add+=2:func_add++){
        ret = MSSP_I2C_Master_Send_Start();
        ret = MSSP_I2C_Master_Write_Blocking(RTC_ADD, &ack);
        ret = MSSP_I2C_Master_Write_Blocking(func_add, &ack);

        ret = MSSP_I2C_Master_Send_Repeated_Satrt();
        ret = MSSP_I2C_Master_Write_Blocking(RTC_ADD | 0x01, &ack);

        switch(func_add)
        {
            case RTC_SECONDES_ADD:
                ret = MSSP_I2C_Master_Read_Blocking(I2C_MASTER_SEND_NACK, &(rtc_obj->second));
                break;
            case RTC_MINUTES_ADD:
                ret = MSSP_I2C_Master_Read_Blocking(I2C_MASTER_SEND_NACK, &(rtc_obj->minute));
                break;
            case RTC_HOURS_ADD:
                ret = MSSP_I2C_Master_Read_Blocking(I2C_MASTER_SEND_NACK, &(rtc_obj->hour));
                break;
            case RTC_DAY_ADD:
                ret = MSSP_I2C_Master_Read_Blocking(I2C_MASTER_SEND_NACK, &(rtc_obj->day));
                break;
            case RTC_MONTH_ADD:
                ret = MSSP_I2C_Master_Read_Blocking(I2C_MASTER_SEND_NACK, &(rtc_obj->month));
                break;
            case RTC_YEAR_ADD:
                ret = MSSP_I2C_Master_Read_Blocking(I2C_MASTER_SEND_NACK, &(rtc_obj->year));
                break;
            default : break; 
        }
        
        ret = MSSP_I2C_Master_Send_Stop();
    }
    
    return ret;
}
