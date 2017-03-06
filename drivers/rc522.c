#include<kernel/fos.h>

void rc522_write_register	(
							uint8_t reg
							,uint8_t value
							)
{
	spi_install(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0);
	digitalWrite(SPI_CE0, LOW);		// Select slave
	spi_putc(reg & 0x7E);				// MSB == 0 is for writing. LSB is not used in address. Datasheet section 8.1.2.3.
	spi_putc(value);
	digitalWrite(SPI_CE0, HIGH);		// Release slave again
}

uint8_t rc522_read_register(
							uint8_t reg
							)
{
	uint8_t value;
	spi_install(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0);
	digitalWrite(SPI_CE0, LOW);			// Select slave
	spi_putc(0x80 | (reg & 0x7E));			// MSB == 1 is for reading. LSB is not used in address. Datasheet section 8.1.2.3.
	value = spi_getc();					// Read the value back. Send 0 to stop reading.
	digitalWrite(SPI_CE0, HIGH);			// Release slave again
	return value;
}
