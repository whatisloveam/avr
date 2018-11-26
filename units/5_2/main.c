#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD =  0b00111000;
	PORTD = 0b00000111;
	int a;
	while(1)
	{
		//a = 255 - PIND;
		if((~PIND & 1) == 1)//00000001
		{
			PORTD = 0b00001111;
			_delay_ms(500);
			PORTD = 0b00000111;
		}
		if((~PIND & 2) == 2)//00000010
		{
			PORTD = 0b00010111;
			_delay_ms(500);
			PORTD = 0b00000111;
		}
		if((~PIND & 4) == 4)//00000100
		{
			PORTD = 0b00100111;
			_delay_ms(500);
			PORTD = 0b00000111;
		}
	}
}
