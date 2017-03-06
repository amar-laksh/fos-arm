#include <kernel/fos.h>

int kmain 	(
			uint32_t r0
			, uint32_t r1
			, uint32_t atags
			)
{
	mini_uart_install();
	gpio_install();
	(void) r0;
	(void) r1;
	(void) atags;
	sprintf("\nR0=0x%x \nR1=0x%x\nATAGS=0x%x\n", r0, r1, atags);
	sprintf("Now I am gonna start to try to communicate with the rfid chip\n");
	while(1){
		sprintf("HELLO\n");
		uint8_t val = rc522_read_register('\x2E');
		sprintf("THIS IS A NICE VALUE:%x\n", val);
	}

	//lcd_install();
	return(0);
}
