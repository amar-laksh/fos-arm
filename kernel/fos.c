#include <kernel/fos.h>


int kmain (uint32_t r0, uint32_t r1, uint32_t atags)
{
	lcd_install();
	//uart_install();
	(void) r0;
	(void) r1;
	(void) atags;
	//gpio_install();
	return(0);
}