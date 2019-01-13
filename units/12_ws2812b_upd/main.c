#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define BitOff    PORTB = 0x00
#define BitOn      PORTB = 0x04

volatile int pos = 0;
int step;

struct Pixel{
	int r,g,b;
} p[30];


void Set0( void ) //���������� � ������ ����� ���� ~0.4 ���
{
	BitOn;asm("nop");asm("nop");asm("nop");BitOff; 
}

void Set1( void ) //���������� � ������ ����� ������� ~0.85 ���
{
	BitOn;asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");BitOff; 
}

void setPixel(int n,int r, int g,int b)
{
	p[n].r = r;
	p[n].g = g;
	p[n].b = b;
}
void showStrip(void)
{
	int a,i,j;
	cli();
	for(i = 0; i < 30; i++)
	{
		a = 0b100000000;
		for(j = 0; j < 8; j++)
		{
			a = a >> 1;
			if((p[i].g & a) == 0) Set0();
			else Set1();
		}
		a = 0b100000000;
		for(j = 0; j < 8; j++)
		{
			a = a >> 1;
			if((p[i].r & a) == 0) Set0();
			else Set1();
		}
		a = 0b100000000;
		for(j = 0; j < 8; j++)
		{
			a = a >> 1;
			if((p[i].b & a) == 0) Set0();
			else Set1();
		}
	}
	sei();
}

void Fill(int r, int g, int b, int pause)
{
	for(int i = 0; i < 30; i++)
	{
		setPixel(i, r, g,b);
		showStrip();
		_delay_ms(pause);
	}
}

void Fill_Inverse(int r, int g, int b, int pause)
{
	for(int i = 29; i >= 0; i--)
	{
		setPixel(i, r, g,b);
		showStrip();
		_delay_ms(pause);
	}
}

void RunningLight(int r, int g, int b, int pause)
{
	for(int i = 0; i < 30; i++)
	{
		if(i !=0) setPixel(i-1, 0, 0,0);
		
		setPixel(i, r, g,b);		
		showStrip();
		_delay_ms(pause);
	}
	setPixel(29, 0,0,0);		
	showStrip();
	_delay_ms(pause);
}
void Blink(int r, int g, int b, int pause, int k)
{
	float stepR=r/k, stepG=g/k, stepB=b/k,red=0,green=0,blue=0;
	
	for(int i = 0; i < k; i++)
	{
		setPixel(3, red, green, blue);
		red += stepR;
		green += stepG;
		blue +=stepB;
		showStrip();
		_delay_ms(pause);
	}	
	for(int i = 0; i < k; i++)
	{
		setPixel(3, red, green, blue);
		red -= step;
		green -= stepG;
		blue -=stepB;
		showStrip();
		_delay_ms(pause);
	}
}

void Sinn(int red, int green, int blue, int pause) 
{
  for(float i=0; i<=6.283; i = i + 0.0175) {
	  setPixel(2, (127*sin(i)+128)/255*red,
				  (127*sin(i)+128)/255*green,
				  (127*sin(i)+128)/255*blue);
      showStrip();
      _delay_ms(pause);
  }
}

ISR(INT0_vect)
{
	if((PIND & 0x08) == 0x08) // B = 1
	{
		pos--;
	}
	else
	{
		pos++;
	}
	_delay_ms(5);
}
ISR(INT1_vect)
{
	if((PIND & 0x04) == 0x04) // B = 1
	{
		pos--;
	}
	else
	{
		pos++;
	}
	_delay_ms(5);
}

int main(void)
{
	DDRB = 0xFF;
	
	DDRD = 0x00;
	PORTD = 0xFF;
	GICR = (1 << INT0) | (1 << INT1);
	MCUCR = (1 << ISC01)|(1<<ISC11)|(1<<ISC10);
	
	//sei();
	int f = 0;
	while(1==1)
	{
		
		Fill(200, 0, 0, 20);
		/*if((PIND & 0x08) != f)
		{
			if((bool)(PIND & 0x04) == (bool)(PIND & 0x08))
			{
				pos--;
			}
			else pos++;
		}
		f = (PIND & 0x08);
		
		Fill(0, 0,0, 0);
		if(pos < 0) pos = 0;
		if(pos > 29) pos = 29;
		setPixel(pos, 150, 0, 0);
		_delay_ms(3);*/
		//Blink(200, 100, 0, 10, 100);
		//Fill(255, 0,0, 20);
		//Fill_Inverse(0,0,0, 20);
		//Fill(0, 0,0, 0);
		//(0, 0, 200, 20);
	}
}