#ifndef SPI_H
#define SPI_H

void SPI_MASTER_Init();
void write_execute(unsigned char CMD, unsigned char data);
void write_smile();
void write_frown();
void display_8x8();

#endif