#include <kernel/fos.h>
/**
 * Steps(Interrupt based)-
 * 1. Set INTR = 1 , INTD = 1
 * 2. Set CPOL = 0 , CPHA = 1, TA = 0
 * 3. Set SCLK = CORE_CLOCK/CDIV
 * 4. if DONE == 1 && First INTR? write Data
 * 5. if DONE == 1 && No Data? set TA = 0
 * 6. if RXR = 1? Read Data
 */

int DATA_CYCLE = 0;
void spi_putc	(
				unsigned char c
				)
{
	while(1){
		if((GET32(SPI_CS) & 0x10000) == 1) break;
	}
	PUT32(SPI_FIFO,c);
}


unsigned char spi_getc()
{
	while(1){
		if((GET32(SPI_CS) & 0x80000) == 1) break;
	}
	return GET32(SPI_FIFO);
}


void spi_install()
{
	PUT32(SPI_CS,(1<<9));
	PUT32(SPI_CS,(1<<10));

	PUT32(SPI_CS,(1<<2));
	PUT32(SPI_CS,(1<<3));

	PUT32(SPI_CS,(1<<7));

	PUT32(SPI_CLK,0);



}
