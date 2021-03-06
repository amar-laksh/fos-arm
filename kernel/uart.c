#include <kernel/fos.h>


/**
 * Steps to install mini_uart
 * 1. Disable the mini UART
 * 2. Setup GPIO Pins 14 and 15(ALT5) & 16 and 17(ALT5)
 * 3. Setup GPIO Function Mode
 * 4. Setup Baudrate
 * 5. Setup Data type
 */


void mini_uart_putc (
					unsigned char c
					)
{
	while(1){
		if(GET32(AUX_MU_LSR_REG)&0x20) break;
	}
	PUT32(AUX_MU_IO_REG, c);

}


unsigned char mini_uart_getc ()
{
	while(1){
		if(GET32(AUX_MU_LSR_REG)&0x01) break;
	}
	return GET32(AUX_MU_IO_REG);

}


void mini_uart_gets (char* buf)
{
	unsigned char ch='0';
	int i=0;
	while((ch = mini_uart_getc()) != 0xa){
		*(buf+i) = ch;
		i++;
	}
	*(buf+i) = '\0';
}


void mini_uart_puts (
					char* s
					)
{
	for(int i=0;i<strlen(s);i++)
		mini_uart_putc(s[i]);
}




void uart_putc  ( 
				unsigned int c 
				)
{
	while(1)
	{
		if((GET32(UART_FR)&0x20)==0) break;
	}
	PUT32(UART_DR,c);
}


void uart_puts (
					char* s
					)
{
	for(int i=0;i<strlen(s);i++)
		uart_putc(s[i]);
}


void uart_install()
{
	unsigned int ra;
	PUT32(UART_CR,0);

	ra=GET32(GPFSEL1);
	ra&=~(7<<12); //gpio14
	ra|=4<<12;    //alt0
	ra&=~(7<<15); //gpio15
	ra|=4<<15;    //alt0
	PUT32(GPFSEL1,ra);

	PUT32(GPPUD,0);
	for(ra=0;ra<150;ra++) dummy(ra);
	PUT32(GPPUDCLK0,(1<<14)|(1<<15));
	for(ra=0;ra<150;ra++) dummy(ra);
	PUT32(GPPUDCLK0,0);

	PUT32(UART_ICR,0x7FF);
	PUT32(UART_IBRD,1);
	PUT32(UART_FBRD,40);
	PUT32(UART_LCRH,0x70);
	PUT32(UART_CR,0x301);
	uart_puts("----THIS IS GARBAGE---\n\033c");
	uart_puts("Hello World from the UART!!\n");
	uart.status = 0;
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
	PUT32(GPPUD, 0);
	delay_c(150);
	PUT32(GPPUDCLK0,(1<<14));
	delay_c(150);
	PUT32(GPPUD, 0);
	PUT32(GPPUDCLK0,0);

	pinMode(15, ALT5);
	PUT32(GPPUD, 0);
	delay_c(150);
	PUT32(GPPUDCLK0,(1<<15));
	delay_c(150);
	PUT32(GPPUD, 0);
	PUT32(GPPUDCLK0,0);


	PUT32(AUX_MU_CNTL_REG,3);
	mini_uart_puts("----THIS IS GARBAGE---\n\033c");
	mini_uart_puts("Hello World from the mini UART!!\n");
	uart.status = 1;
}
