#include <kernel/fos.h>


/**
 * Steps to install mini_uart
 * 1. Disable the mini UART
 * 2. Setup GPIO Pins 14 and 15(ALT5) & 16 and 17(ALT5)
 * 3. Setup GPIO Function Mode
 * 4. Setup Baudrate
 * 5. Setup Data type
 */


void mini_uart_putc(unsigned char c){
	while(1){
		if(GET32(AUX_MU_LSR_REG)&0x20) break;
	}
	PUT32(AUX_MU_IO_REG, c);

}

void mini_uart_install()
{
	PUT32(AUX_ENABLES, 0x007);
	PUT32(AUX_MU_IER_REG,0);
	PUT32(AUX_MU_CNTL_REG,0);
	PUT32(AUX_MU_LCR_REG,3);
	PUT32(AUX_MU_MCR_REG,0);
	PUT32(AUX_MU_IER_REG,0);

	PUT32(AUX_MU_IIR_REG,0xC6);
	PUT32(AUX_MU_BAUD_REG,270);

	pinMode(14, ALT5);
	
	pullUpDownWrite(0);
	delay(150);
    PUT32(GPPUDCLK0,(1<<14));
    delay(150);
    PUT32(GPPUDCLK0,0);

    PUT32(AUX_MU_CNTL_REG,2);
    pinMode(35, OUTPUT);
	pinMode(47, OUTPUT);
	int i;
    for(i = 0;i < 10; i++)
    {
    	mini_uart_putc('a');
        digitalWrite(35, HIGH);
		digitalWrite(47, HIGH);
		delay(0x100000);
		mini_uart_putc('b');
        digitalWrite(35, LOW);
		digitalWrite(47, LOW);
		delay(0x100000);
    }
}
