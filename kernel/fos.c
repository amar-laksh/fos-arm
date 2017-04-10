#include <kernel/fos.h>
int cmds = 5;
char* commands[5]={
	"LED 1"
	,"LED 0"
	,"lsgpio"
	,"help"
	,"?"
};

void do_this(int i, char* buff){
	sprintf("IN DO THIS");
	switch(i){
		case 0:
				pinMode(35, OUTPUT);
				digitalWrite(35, HIGH);
				sprintf("Setting the LED to HIGH\n");
				pinMode(16, OUTPUT);
				digitalWrite(16, HIGH);
				break;
		case 1:
				pinMode(35, OUTPUT);
				digitalWrite(35, LOW);
				sprintf("Setting the LED to LOW\n");
				pinMode(16, OUTPUT);
				digitalWrite(16, LOW);
				break;
		case 3:
		case 4:
				sprintf("The available commands are:\n");
				for (int i = 0; i < cmds; ++i){
					sprintf("%s\n", commands[i]);
				}
				break;
		default:
				sprintf("Sorry command not found");
	}
}

void process_buffer(char* buff){
	for(int i=0;i<cmds;i++){
		if(equals(buff, commands[i]) == 0){
			do_this(i, buff);
		}
	}
}


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

	//sprintf("\nR0=0x%x \nR1=0x%x\nATAGS=0x%x\n", r0, r1, atags);
	char s[100];

	while(1){
		mini_uart_gets(s);
		sprintf("RECIEVED: %s\n", s);
		process_buffer(s);
	}

	//lcd_install();
	return(0);
	}