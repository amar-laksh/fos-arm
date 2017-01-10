#include <kernel/fos.h>


void lcd_install()
{
	pinMode(35, OUTPUT);
	pinMode(47, OUTPUT);
	pinMode(18, INPUT);
	PUT32(GPPUD, 2);
	delay(150);
	PUT32(GPPUDCLK0, (1<<18));
	delay(150);
	PUT32(GPPUD, 0);
	PUT32(GPPUDCLK0, 0);
	
	while(1){
		if(digitalRead(18)){
			digitalWrite(35, HIGH);
			delay(0x100000);
			digitalWrite(47, LOW);
			delay(0x100000);
			}
		else{
			digitalWrite(35, LOW);
			delay(0x100000);
			digitalWrite(47, HIGH);
			delay(0x100000);
		}
	}
}
