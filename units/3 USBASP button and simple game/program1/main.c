#include <avr/io.h>
#include <util/delay.h>
int main(void) { 
	DDRB = 0xFF;

	while(1) 
	{ 
		PORTB = 0b00000001;
		_delay_ms(400);
		PORTB = 0x00;
		_delay_ms(400);
	} 
	return 0;
}
  