#include <avr/io.h>
#include <util/delay.h>

int znaki[21] = 	//    a b c d e f g dot
		{0b11111100,// 0//1,1,1,1,1,1,0,0},//0
		 0b01100000,// 1
		 0b11011010,// 2
		 0b11110010,// 3
		 0b01100110,// 4
		 0b10110110,// 5
		 0b10111110,// 6
		 0b11100000,// 7 
		 0b11111110,// 8
		 0b11110110,// 9
		 0b01101110,// H 10
		 0b10011110,// E 11
		 0b00011100,// L 12
		 0b11011110,// A 13
		 0b01110110,// Y 14
		 0b01111100,// U 15
		 0b10001110,// F 16
		 0b10011100,// C 17
		 0b11111100,// O 18
		 0b10110110,// S 19
		 0b01101110};//K 20
		 
				
		 
int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
	DDRB = 0b11111100;//0xFC//253
	PORTB = 0xFF;
	while(1==1)
	{
		//0b11111011;0xFB
		PORTB = 0xFB;
		PORTD = znaki[12];
	}
	return 0;
}



































#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRD = 0xFF;
	PORTD= 0x00;
	
	DDRB = 0b00000000;
	PORTB= 0x07;
	for(;;)
	{
		if((~PINB & 1) == 1)
		{
			PORTD = 0x01;
			_delay_ms(200);
			PORTD = 0x00;
		}
	}
	return 0;
}