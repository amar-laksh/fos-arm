#include <kernel/fos.h>
/**
 * Steps(Interrupt based)-
 * 1. Set INTR = 1 , INTD = 1
 * 2. Set CPOL = 0 	, CPHA = 1, TA = 0
 * 3. Set SCLK = CORE_CLOCK/CDIV
 * 4. if DONE == 1 && First INTR? write Data
 * 5. if DONE == 1 && No Data? set TA = 0
 * 6. if RXR = 1? Read Data
 *
 */

void spi_putc	(
				unsigned char c
				)
{
	PUT32(SPI_CS,(1<<7));
	while((GET32(SPI_CS) & 0x40000) != 0){
		PUT32(SPI_FIFO,c);
	}
	PUT32(SPI_CS,(0<<7));
}


unsigned char spi_getc()
{
	PUT32(SPI_CS,(1<<7));
	unsigned char fifo_byte = 0x0;
	while((GET32(SPI_CS) & 0x20000) != 0){
			fifo_byte = GET32(SPI_FIFO);
	}
	PUT32(SPI_CS, (0<<7));
	return fifo_byte;
}


void spi_install(
				enum SPI_SPEED speed
				, enum SPI_MODE mode
				)
{
	pinMode(11, ALT0);

	pinMode(10, ALT0);

	pinMode(9, ALT0);

	if(mode == SPI_MODE0){
		PUT32(SPI_CS, (0<<2));
		PUT32(SPI_CS, (0<<3));
	}
	else if(mode == SPI_MODE1){
		PUT32(SPI_CS, (1<<2));
		PUT32(SPI_CS, (0<<3));
	}

	else if(mode == SPI_MODE2){
		PUT32(SPI_CS, (0<<2));
		PUT32(SPI_CS, (1<<3));
	}

	else if(mode == SPI_MODE3){
		PUT32(SPI_CS, (1<<2));
		PUT32(SPI_CS, (1<<3));
	}
	PUT32(SPI_CLK, speed);
}
