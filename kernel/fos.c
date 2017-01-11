#include <kernel/fos.h>


int kmain (uint32_t r0, uint32_t r1, uint32_t atags)
{
	mini_uart_install();
	gpio_install();
	(void) r0;
	(void) r1;
	(void) atags;
	
	//lcd_install();
	return(0);
}
