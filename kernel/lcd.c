#include <kernel/fos.h>


void lcd_install()
{
	pinMode(OK_LED, OUTPUT);
	pinMode(17, INPUT);
	
	while(1){
		if(digitalRead(17)){
			digitalWrite(OK_LED, HIGH);
			delay(1);
			}
		else{
			digitalWrite(OK_LED, LOW);
			delay(1);
		}
	}
}
