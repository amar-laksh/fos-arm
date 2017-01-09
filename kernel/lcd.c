#include <kernel/fos.h>


void lcd_install()
{
	pinMode(35, OUTPUT);
	pinMode(47, OUTPUT);

	pinMode(18, INPUT);
	while(1){
		if(digitalRead(18) == 1){
			digitalWrite(35, HIGH);
			delay(0x300000);
		}
		digitalWrite(35, LOW);
		digitalWrite(47, LOW);
	}
}
