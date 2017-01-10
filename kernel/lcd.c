#include <kernel/fos.h>


void lcd_install()
{
	pinMode(OK_LED, OUTPUT);
	pinMode(18, INPUT);
	
	PUT32(GPPUD, 2);
	delay(150);
	PUT32(GPPUDCLK0, (1<<18));
	delay(150);
	PUT32(GPPUD, 0);
	PUT32(GPPUDCLK0, 0);
	
	while(1){
		if(digitalRead(18)){
			digitalWrite(OK_LED, HIGH);
			delay(0x100000);
			}
		else{
			digitalWrite(OK_LED, LOW);
			delay(0x100000);
		}
	}
}
