//#define F_CPU 1000000UL
#include <avr/io.h>
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





PORTB	DDRB
PORTC	DDRC
PORTD	DDRD