#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
int a = 64;
int b = 32;
int c = 16;
int d = 8;
int e = 4;
int f = 2;
int g = 1;

int shift = 0;
int count = 0,s = 0,m = 0;
unsigned char ar[10], buffer[4];

void displayNum(int num, int bit)
{
	PORTB = ~(1 << bit);
	PORTD = ar[num];	
}

ISR (TIMER0_OVF_vect) //interrupt sevice routine
{
	if(count++ > 15) 
	{
	s++;
	count = 0;
	}
	if(s >= 60) 
	{
		s = 0;
		m++;
	}
	buffer[0] = m / 10;
	buffer[1] = m % 10;
	buffer[2] = s / 10;
	buffer[3] = s % 10;
	shift++;
	if(shift == 4) shift = 0;
	if(shift == 0) displayNum(buffer[0], 0);
	if(shift == 1) displayNum(buffer[1], 1);
	if(shift == 2) displayNum(buffer[2], 2);
	if(shift == 3) displayNum(buffer[3], 3);
}
int main(void)
{
	ar[0] = a+b+c+d+e+f;
	ar[1] = b+c;
	ar[2] = a+b+d+e+g;
	ar[3] = a+b+c+d+g;
	ar[4] = b+c+f+g;
	ar[5] = a+f+g+c+d;
	ar[6] = a+f+g+c+d+e;
	ar[7] = a+b+c;
	ar[8] = 255;
	ar[9] = 255 - e;
	
	DDRB = 0xFF;
	DDRD = 0xFF;
		
	PORTD = ar[0];
	sei();// set interrupt enable
	
	TIMSK = (1<<TOIE0);
	//clock select global offensive
	TCCR0 = (0<<CS02)|(0<<CS01)|(1<<CS00);
	
	while(1);
	return 0;
}