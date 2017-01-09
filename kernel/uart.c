#include <kernel/fos.h>


/**
 * Steps to install mini_uart
 * 1. Disable the mini UART
 * 2. Setup GPIO Pins 14 and 15
 * 3. Setup GPIO Function Mode
 * 4. Setup Baudrate
 * 5. Setup Data type
 */

void mini_uart_install()
{
	PUT32(AUX_ENABLES, 0x007);
	
}
