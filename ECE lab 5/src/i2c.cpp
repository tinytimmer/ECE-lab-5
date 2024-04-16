#include "i2c.h"
#include <avr/io.h>
#include "Arduino.h"

//i put in a wait to complete definition to check if TWCR is off or on and if TWINT is enabled (at least I think thats what I put haha)
#define wait_completion while(!(TWCR & (1 << TWINT)));


void initI2C(){
    PRR0 &= ~(1 << PRTWI);  // init I2C module
    TWSR |= (1 << TWPS0);  // prescaler power = 1
    TWSR &= ~(1 << TWPS1); // prescaler power = 1 
    TWBR = 0xC6; // bit rate generator = 10k  (TWBR = 198)
    TWCR |= (1 << TWINT )|(1 << TWEN); // enable two wire interface
}

void StartI2C_Trans(unsigned char SLA){
    //  function initiates a start condition and calls slave device with SLA
    TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN); // clear TWINT, intiate a start condition, initiate enable
    wait_completion;
    TWDR = (SLA << 1); // // Set two wire data register to the SLA + write bit
    TWCR = (1 << TWINT)|(1 << TWEN);  // Trigger action: Clear TWINT and initiate enable
    wait_completion;
}

void StopI2C_Trans(){
    // this function sends a stop condition to stop I2C transmission
    TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO); //trigger action+stop condition
}

void writeTo(unsigned char SLA, unsigned char REGADDRESS, unsigned char data){
    StartI2C_Trans(SLA);
    write(REGADDRESS);
    write(data);
    StopI2C_Trans();
}

void write(unsigned char data){
    // function loads the data passed into the I2C data register and transmits it
    TWDR = data; //Set two wire data register equal to incoming data
    TWCR = (1 << TWINT)|(1 << TWEN);  // trigger action: clear flag and enable TWI
    wait_completion;
}

void Read_from(unsigned char SLA, unsigned char MEMADDRESS){
    // this function sets up reading from SLA at the SLA MEMADDRESS 
    StartI2C_Trans(SLA);
    //Serial.println("Start Finish");
    write(MEMADDRESS);
    //Serial.println("Write Finish");
    
    TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);  // Clear TWINT, initiate start condition, initiate enable
    wait_completion;
    //Serial.println("Clear Finish");

    TWDR = (SLA << 1)|0x01; // Set two wire data register to the SLA + read bit
    TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWEA);// trigger with master sending ack
    wait_completion;
    //Serial.println("Set Finish");

    TWCR = (1 << TWINT)|(1 << TWEN);  // master can send a nack now
    wait_completion;
    //Serial.println("Trigger Finish");

    TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO); // Stop condition
    //Serial.println("Read Finish");
}

unsigned char Read_data(){
    // Returns the last byte from the data register
    return TWDR;
}
