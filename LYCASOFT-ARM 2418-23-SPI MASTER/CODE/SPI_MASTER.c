#include <lpc214x.h>
#include "LPC2148_delay.h"
#include "LPC2148_LCD_4_BIT_HEADER_FILE.h"

void SPI_Initialization()
{
	PINSEL0 = PINSEL0 | 0x00001500;			/* Select P0.4, P0.5, P0.6, P0.7 as SCK0, MISO0, MOSI0 and GPIO */
	IODIR0=1<<7;
	IOCLR0=1<<7;
	S0SPCR = 0x087C; 										/* SPI Master mode, 8-bit data, SPI0 mode */
	S0SPCCR = 0x8; 											/* Even number, minimum value 8, pre scalar for SPI Clock */
}

void SPI_Send_Data(unsigned char x)
{
	IO0CLR = (1<<7);										/* SSEL = 0, enable SPI communication with slave */
	S0SPDR = x;													/* Load data to be written into the data register */
	while (!((S0SPSR & 0x80) == 0X80));	/* Wait till data transmission is completed */
	S0SPDR = 0X00;
	IO0SET = (1<<7);										/* SSEL = 1, disable SPI communication with slave */
}

void SPI_String(const unsigned char *Str)
{
	while(*Str != 0)
	{
		SPI_Send_Data(*Str++);
		delay(15);
	}
}
//char SPI_Read()
//{
//	IO0CLR = (1<<7);										/* SSEL = 0, enable SPI communication with slave */
//	S0SPDR = 0xFF;											/* Transmit Flush byte */
//	while ( (S0SPSR & 0x80) == 0 );			/* Wait till data transmission is completed */
//	IO0SET = (1<<7);										/* SSEL = 1, disable SPI communication with slave */
//	return S0SPDR;											/* Return the data received */
//}

int main()
{
	PINSEL2 = 0x00000000;
	IODIR1 = 0x3F0 << 16;
	
	Lcd_Intialization();
	SPI_Initialization();
	
	Lcd_Command(0x80);
	Lcd_String("LYCASOFT");
	
	while(1)
	{
		SPI_String("LYCASOFT");
	}
}