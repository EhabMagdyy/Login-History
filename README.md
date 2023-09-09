# Login-History

![Screenshot 2023-09-09 174125](https://github.com/EhabMagdyy/Login-History/assets/132620660/4520b10e-d3f6-4716-bcb3-738284fcf77d)

### Description
When the user login successfully the Master(PIC18F4620) will receive the date and time of login from Real time clock via I2C protocol,
Then send it to the slave(Atmega32) via SPI protocol. 
The slave will store the date and time in new location at EEPROM via I2C protocol, then display the last login date at LCD.
