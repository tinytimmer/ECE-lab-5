// this will be what the 8x8 matrix LEDs connect to
#include "spi.h"
#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>

//here are definitions for this function, will be explained per define
#define DDR_SPI DDRB // Data Direction Register on ATMEGA2560 for SPI is DDRB
#define DD_SS DDB0  // SS Chip Select data direction bit B0 of ATMEGA2560 is DDB0, pin 53 on board
#define DD_SCK DDB1  // Clock pin connection data direction bit B1 on ATMEGA2560 is DDB1, pin 52 on board
#define DD_MOSI DDB2 // MOSI pin datadirection on ATMEGA2560 is DDB0, pin 53 on board
#define SPI_PORT PORTB // PortB for SPI on ATMEGA2560 is PORTB
#define SPI_SS_BIT PORTB0 // Port B register Bit B0 of Chip Select on ATMEGA2560 is PORTB0, pin 53 on board

//check to see if its done with the job, otherwise wait for completion
#define wait_complete while(!(SPSR & (1 << SPIF)));

void MASTER_Init_spi(){
    // set MOSI,SCK,and SS direction to outputs
    //quick note: program SHOULD NOT use MOSI line as it SHOULD ONLY write to the device
    DDR_SPI = (1 << DD_MOSI)|(1 << DD_SCK)|(1 << DD_SS);

    // set SS high initially (chip select off)
    SPI_PORT |= (1 << SPI_SS_BIT);

    // enable SPI, master mode, CPOL, CPHA, default clock and fosc/128
    // datasheet says sample on rising edge is CPOL = 1 CPHA =1
    SPCR |= (1 <<SPE)|(1 << MSTR)|(1 << CPOL)|(1 << CPHA )|(1 << SPR1)|(1 << SPR0);

}

void write_execute(unsigned char CMD, unsigned char data){
    SPI_PORT &= ~(1 << SPI_SS_BIT);  // enable chip select bit to begin SPI frame
    SPDR = CMD; // load the CMD address into register
    wait_complete; // wait for flag to raise
    SPDR = data; // load the data into register
    wait_complete; // wait for flag to raise
    SPI_PORT |= (1 << SPI_SS_BIT); // disable chip select to end SPI frame
}