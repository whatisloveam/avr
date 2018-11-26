#include <avr/io.h>
#include <util/delay.h>
int main(void) {
	DDRD = 0x00;
	DDRB = 0xFF;
	PORTD = 0xFF;
	PORTB = 0x00;
	while(1 == 1)
	{
		if(PIND & 0x08)
		{
			PORTB = !PORTB;
		}
	}
	return 0;
}