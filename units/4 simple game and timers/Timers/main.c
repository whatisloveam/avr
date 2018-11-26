#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned int count = 0;

ISR (TIMER0_OVF_vect)
{
	count++;
	if(count > 490)
	{
		PORTD = !PORTD;
		count = 0;
	}
}

int main(void)
{
	DDRD = 0xFF;
	TCCR0 = 0b00000010;
	TIMSK = (1<<TOIE0);
	asm("sei");
	while(1==1)
	{
		asm("nop");
	}
	return 0;
}