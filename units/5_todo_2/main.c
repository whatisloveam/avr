#include <avr/io.h>

int main(void)
{
	//  abcdefg
	// 0100 0000 // 0x40
	//  64 
	//P76543210
	DDRD = 0xFF;//0b11111111; 255
	PORTD = 0b01000000;
	while(1);
	return 0;
}