#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
int a = 64;
int b = 32;
int c = 16;
int d = 8;
int e = 4;
int f = 2;
int g = 1;

unsigned char ar[10];

int main(void)
{
	unsigned char phrase[] = 
     // f		  u		 c			k      //y   o
	{255-b-c-d,255-a-g,255-b-c-g,255-a-d,0,255-a-d-e,255-g,
	 255-a-g, 255-d, 255-b-e, 255-b-c, d+e+f,255-b-c-d};
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
	int c = 0;
	DDRB = 0x00;
	PORTB = 0x07;
	DDRD = 0xFF;
	PORTD = ar[0];
	while(1)
	{
		if((~PINB & 0x01) == 0x01)
		{
			c++;
			if(c>=10) c=9;
			PORTD = ar[c];
			_delay_ms(200);
		}
		if((~PINB & 0x02) == 0x02)
		{
			c--;
			if(c<0) c=0;
			PORTD = ar[c];
			_delay_ms(200);
		}
		if((~PINB & 0x04) == 0x04)
		{
			c = 0;
			PORTD = ar[0];
		}
		if(((~PINB & 0x01) == 0x01)
		&&
		((~PINB & 0x02) == 0x02)
		&&
		((~PINB & 0x04) == 0x04))
		{
			for(int i=0; i<=12; i++)
			{
				PORTD = phrase[i];
				_delay_ms(400);
			}
		}
	}
	return 0;
}