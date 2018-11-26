#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRB=0x01;
	PORTB = 0x06;
	while (1)
	{
		if((PINB & 0x02) ==0)
		{
			PORTB=0x07;
			_delay_ms(100);
			PORTB=0x06;
			_delay_ms(100);
		}
		if((PINB & 0x04) ==0x04)
		{
			PORTB=0x07;
			_delay_ms(100);
			PORTB=0x06;
			_delay_ms(100);
		}
	}
	return 0;
}