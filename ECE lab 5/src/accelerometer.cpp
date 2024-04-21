#include "accelerometer.h"
#include "i2c.h"
#include <avr/io.h>
#include "Arduino.h"

//I felt that I had to add this in to make the accelerometer to work, I hope it works on yalls end too

#define wait_completion while(!(TWCR & (1 << TWINT)));
#define WRITE_BIT 0;
#define READ_BIT 1;

//accelerometer data, if something is incorrect go ahead and change it and let the others know too
#define MPU_XOUT_H 0x3B
#define MPU_XOUT_L 0x3C
#define MPU_YOUT_H 0x3D
#define MPU_YOUT_L 0x3E
#define MPU_ZOUT_H 0x3F
#define MPU_ZOUT_L 0x40
#define MPU_WHO_AM_I 0x68        //I2C addy
#define MPU_PWR_MANAGEMENT_1_REG 0x6B  
#define MPU_PWR_CONFIG  0x00 //sets internal accel clock to X-gyro for improved stability (datasheet recommended) 
                             //disables temp sensor (not needed for this lab)
                             //wakes up device
#define MPU_PWR_RESET 0x70  //resets all registers in accel to defaults
#define MPU_PWR_MANAGEMENT_2 0x6C

void initAccelerometer(){
     StartI2C_Trans(MPU_WHO_AM_I);
    //  Serial.println(TWSR & (0xF8),HEX); // print out status register to verify transmission, used to check
    //  Serial.flush();

    write(MPU_PWR_MANAGEMENT_1_REG);
    // Serial.println(TWSR & (0xF8),HEX); // print out status register to verify transmission, used to check
    // Serial.flush();

    write(MPU_PWR_CONFIG);
    // Serial.println(TWSR & (0xF8),HEX); // print out status register to verify transmission, use to check
    // Serial.flush();

    StopI2C_Trans(); //stop i2c transmission with MPU. 

}
