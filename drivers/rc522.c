#include<kernel/fos.h>

void rc522_write_register	(
							uint8_t reg
							,uint8_t value
							)
{
	spi_install(SPI_CLOCK_DIV4, SPI_MODE0);
	pinMode(SPI_CE0, ALT0);
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
	spi_install(SPI_CLOCK_DIV4, SPI_MODE0);
	pinMode(SPI_CE0, ALT0);
	digitalWrite(SPI_CE0, LOW);			// Select slave
	sprintf("Before putc\n");
	spi_putc(0x80 | (reg & 0x7E));			// MSB == 1 is for reading. LSB is not used in address. Datasheet section 8.1.2.3.
	sprintf("After putc\n");
	value = spi_getc();					// Read the value back. Send 0 to stop reading.
	sprintf("After getc\n");
	digitalWrite(SPI_CE0, HIGH);			// Release slave again
	return value;
}

void rc522_reset() {
	rc522_write_register(0x01, 0x0F);	// Issue the SoftReset command.
	// The datasheet does not mention how long the SoftRest command takes to complete.
	// But the MFRC522 might have been in soft power-down mode (triggered by bit 4 of CommandReg) 
	// Section 8.8.2 in the datasheet says the oscillator start-up time is the start up time of the crystal + 37,74μs. Let us be generous: 50ms.
	delay_c(50);
	// Wait for the PowerDown bit in CommandReg to be cleared
	while (rc522_read_register(0x01) & (1<<4)) {
		// PCD still restarting - unlikely after waiting 50ms, but better safe than sorry.
	}
} // End PCD_Reset()


void rc522_install()
{
	// Set the chipSelectPin as digital output, do not select the slave yet
	pinMode(SPI_CE0, OUTPUT);
	digitalWrite(SPI_CE0, HIGH);
	
	// Set the resetPowerDownPin as digital output, do not reset or power down.
	pinMode(SPI_RST, INPUT);
	
	if (digitalRead(SPI_RST) == LOW) {	//The MFRC522 chip is in power down mode.
		pinMode(SPI_RST, OUTPUT);
		delay_c(500);
		digitalWrite(SPI_RST, HIGH);		// Exit power down mode. This triggers a hard reset.
		// Section 8.8.2 in the datasheet says the oscillator start-up time is the start up time of the crystal + 37,74μs. Let us be generous: 50ms.
		delay_c(50);
	}
	else { // Perform a soft reset
		rc522_reset();
	}
}