#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD =  0b00111000;
	PORTD = 0b00000111;
	while(1)
	{
		if(~PIND & 0x01== 1)
		{
			PORTD = 0b00001111;
			_delay_ms(500);
			PORTD = 0b00000111;
		}
		if(~PIND & 0x02== 0x02)
		{
			PORTD = 0b00010111;
			_delay_ms(500);
			PORTD = 0b00000111;
		}
		/*if(PIND & 4 == 4)
		{
			PORTD = 0b00100111;
			_delay_ms(500);
			PORTD = 0b00000111;
		}*/
	}
	
}