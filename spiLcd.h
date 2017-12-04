#ifndef SPILCD_H
#define SPILCD_H

//Lcd instructions
#define LCD_DISPLAYCONTROL 0x08

//display control flags
#define LCD_DISPLAYON      0x04

#define PIN_ENABLE 4
#define PIN_RS 6
#define PIN_BACKLIGHT 7

#define CMD_WRITE 0x40
#define CMD_READ  0x41

#define IODIRA   0x00
#define IODIRB   0x01
#define GPINTENA 0x04
#define GPINTENB 0x05
#define INTCAPA  0x10
#define INTCAPB  0x11
#define GPIOA    0x12
#define GPIOB    0x13
#define OLATA    0x14
#define OLATB    0x15

int gpio_reg;
int spi_fd;

void setDefaultHd44780 (hd44780 * header);
void initialiseDisplay (hd44780 * header);
void writeBytes (hd44780 * header, int byte, int mode);
void readBytes (hd44780 * header, int reg);
void delay (unsigned int howLong);

#endif
