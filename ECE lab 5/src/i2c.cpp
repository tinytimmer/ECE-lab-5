#include "i2c.h"
#include <avr/io.h>
#include "Arduino.h"

//i put in a wait to complete definition to check if TWCR is off or on and if TWINT is enabled
#define wait_completion while(!(TWCR & (1 << TWINT)));


void initI2C(){
    PRR0 &= ~(1 << PRTWI);  // wake up I2C module on power management register
    TWSR |= (1 << TWPS0);  // prescaler power = 1
    TWSR &= ~(1 << TWPS1); // prescaler power = 1 
    //remember to find TWBR is the following: 𝑇𝑊𝐵𝑅=((𝐶𝑃𝑈 𝐶𝑙𝑜𝑐𝑘 𝑓𝑟𝑒𝑞𝑢𝑒𝑛𝑐𝑦)/(𝑆𝐶𝐿 𝑓𝑟𝑒𝑞𝑢𝑒𝑛𝑐𝑦)−16)/(2∗〖(4)〗^𝑇𝑊𝑃𝑆 )
    TWBR = 0xC6; // bit rate generator = 10k  (TWBR = 198)
    TWCR |= (1 << TWINT )|(1 << TWEN); // enable two wire interface
}

void StartI2C_Trans(unsigned char SLA){
    //  function initiates a start condition and calls slave device with SLA
    TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN); // clear TWINT, intiate a start condition and enable
    wait_completion;
    TWDR = (SLA << 1); // slave address + write bit '0'
    TWCR = (1 << TWINT)|(1 << TWEN);  // trigger action: clear flag and enable TWI
    wait_completion;
}

void StopI2C_Trans(){
    // this function sends a stop condition to stop I2C transmission
    TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO); //trigger action:  send stop condition
}

void writeTo(unsigned char SLA, unsigned char REGADDRESS, unsigned char data){
    //here we write to the things in () above, while calling on some other functions to do it
    StartI2C_Trans(SLA);
    write(REGADDRESS);
    write(data);
    StopI2C_Trans();
}

void write(unsigned char data){
    // function loads the data passed into the I2C data register and transmits it
    TWDR = data; //load data into TWDR register
    TWCR = (1 << TWINT)|(1 << TWEN);  // trigger action: clear flag and enable TWI
    wait_completion;
}

void Read_from(unsigned char SLA, unsigned char MEMADDRESS){
    // this function sets up reading from SLA at the SLA MEMADDRESS 
    StartI2C_Trans(SLA);
    write(MEMADDRESS);
    
    TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN); // restart to switch to read mode
    wait_completion;
    TWDR = (SLA << 1)|0x01; // 7 bit address for slave plus read bit
    TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWEA);// trigger with master sending ack
    wait_completion;
    TWCR = (1 << TWINT)|(1 << TWEN);  // master can send a nack now
    wait_completion;
    TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO); // Stop condition
    // after this function is executed the TWDR register has the data from SLA that Master wants to read. Hooray!
}

unsigned char Read_data(){
    // Returns the last byte from the data register
    return TWDR;
}
